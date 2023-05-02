/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/02 17:00:27 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespaces(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	(*i)--;
}

t_lex	*lexer(char *input)
{
	t_data	h;
	t_lex	*lex;

	h.i = -1;
	lex = NULL;
	h.s = NULL;
	while (input[++h.i])
	{
		if (input[(h.i)] == '\'' || input[h.i] == '\"')
			dqoute_handler(input, &h, &lex);
		else if (input[h.i] && (input[h.i] == ' ' || input[h.i] == '\t'))
			skip_whitespaces(input, &h.i);
		else
		{
			while (input[h.i] != ' ' && input[h.i] != '\t' && input[h.i])
				h.s = ft_strjoin_characters(h.s, input[h.i++]);
			ft_lstadd_back_lexer(&lex, new_lex(h.s, WORD, 0));
		}
		free(h.s);
		h.s = NULL;
		if (!input[h.i])
			break ;
	}
	return (lex);
}

void	assign_type(t_lex *p)
{
	int		i;
	t_lex	*tmp;

	tmp = p;
	i = 0;
	while (p)
	{
		if (!ft_strcmp("|", p->str))
			p->type = PIPE;
		else if (!ft_strcmp(">", p->str) && !p->ds_quote)
			p->type = REDIRECT;
		else if (!ft_strcmp(">>", p->str) && !p->ds_quote)
			p->type = APPEND;
		else if (!ft_strcmp("<", p->str) && !p->ds_quote)
			p->type = READ_INPUT;
		else if (!ft_strcmp("<<", p->str) && !p->ds_quote)
			p->type = HEREDOC;
		else
			p->type = WORD;
		p = p->next;
	}
	p = tmp;
}

char	*insert_spaces(char *input)
{
	int		i;
	char	*ret;
	char	character;

	i = -1;
	ret = NULL;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			character = input[i];
			ret = ft_strjoin_characters(ret, input[i++]);
			while (input[i] != character && input[i])
				ret = ft_strjoin_characters(ret, input[i++]);
			ret = ft_strjoin_characters(ret, input[i]);

		}
		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			character = input[i];
			ret = ft_strjoin_characters(ret, ' ');
			while (input[i] == character && input[i])
			{
				if (input[i + 1] != character)
					break ;
				ret = ft_strjoin_characters(ret, input[i++]);
			}
			ret = ft_strjoin_characters(ret, input[i]);
			ret = ft_strjoin_characters(ret, ' ');
		}
		else
			ret = ft_strjoin_characters(ret, input[i]);
	}
	return (ret);
}

void	handle_until_pipe(t_lex *p)
{
	int		i;
	t_lex	*tmp;

	i = 0;
	tmp = p;
	while (p)
	{
		if (p->type == PIPE)
			break ;
		if (p->type == WORD && !i)
		{
			p->type = COMMAND;
			i = 1;
		}
		else if (p->type == WORD)
			p->type = ARGUMENT;
		else if ((p->type == REDIRECT || p->type == APPEND)
			&& p->next != NULL && p->next->type == WORD)
			p->next->type = OUT_FILE;
		else if (p->type == READ_INPUT && p->next && p->next->type == WORD)
			p->next->type = IN_FILE;
		else if (p->type == HEREDOC && p->next->type == WORD)
			p->next->type = HEREDOC_DEL;
		p = p->next;
	}
}

void	manage_type(t_lex *p)
{
	t_lex	*tmp;

	tmp = p;
	while (p)
	{
		handle_until_pipe(p);
		p = p->next;
	}
}

void	handle_env(char	*s, char **ret, char **env, int *i)
{
	char	*tmp;
	char	*holder;
	int		j;

	j = 0;
	tmp = NULL;
	holder = NULL;
	(void)ret;
	(void)env;
	while (s[*i] && s[*i] == '$')
		(*i)++;
	while (s[*i] && ft_isalnum(s[*i]))
	{
		tmp = ft_strjoin_characters(tmp, s[*i]);
		if (!ft_isalnum(s[*i + 1]) || !s[*i + 1])
			break ;
		(*i)++;
	}
	holder = get_env(env, tmp);
	*ret = ft_strjoin(*ret, holder);
	free(holder);
	free(tmp);
	tmp = NULL;
	holder = NULL;
}

void	handle_double_quote(char *s, char **ret, char **env, int *i)
{
	*ret = ft_strjoin_characters(*ret, s[*i]);
	(*i)++;
	while (s[*i] && s[*i] != '\"')
	{
		if (s[*i] == '$' && s[*i + 1] != '\"'
			&& s[*i + 1] != ' ' && s[*i + 1] != '\t')
			handle_env(s, ret, env, i);
		else
			*ret = ft_strjoin_characters(*ret, s[*i]);
		if (s[*i] == '\"' || !s[*i])
			break ;
		(*i)++;
	}
	if (!s[*i])
		printf("minishell : error in quotation\n");
	else if (s[*i] == '\"')
		*ret = ft_strjoin_characters(*ret, s[*i]);
	(*i)++;
	if (s[*i] == '\"')
		handle_double_quote(s, ret, env, i);
	else
		*ret = ft_strjoin_characters(*ret, s[*i]);
}

void	handle_single_quote(char *s, int *i, char **ret)
{
	*ret = ft_strjoin_characters(*ret, s[*i]);
	(*i)++;
	while (s[*i] && s[*i] != '\'')
	{
		*ret = ft_strjoin_characters(*ret, s[*i]);
		(*i)++;
	}
	if (!s[*i])
		printf("minishell : error in quotation\n");
	else
		*ret = ft_strjoin_characters(*ret, s[*i]);
	(*i)++;
	if (s[*i] == '\'')
		handle_single_quote(s, i, ret);
	else
		*ret = ft_strjoin_characters(*ret, s[*i]);
	printf("ret = |%s|\n", *ret);
}

void	handle_heredoc(char *s, int *i, char **ret)
{
	while (s[*i] && s[*i] == '<')
	{
		*ret = ft_strjoin_characters(*ret, s[*i]);
		(*i)++;
	}
	(*i)--;
	while (s[*i] && s[*i] == ' ')
	{
		*ret = ft_strjoin_characters(*ret, s[*i]);
		(*i)++;
	}
	while (s[*i])
	{
		if (ft_strchr("|>< ", s[*i]))
			break ;
		*ret = ft_strjoin_characters(*ret, s[*i]);
		(*i)++;
	}
}

void	handle_dollar(char *s, int *i, char **ret, char **env)
{
	char	*tmp;

	tmp = NULL;
	if (s[*i] == '$' && s[*i + 1] != ' ' && s[*i + 1] != '\t' && s[*i + 1])
	{
		(*i)++;
		while (s[*i] && ft_isalnum(s[*i]))
		{
			tmp = ft_strjoin_characters(tmp, s[*i]);
			if (!s[*i + 1] || s[*i + 1] == ' '
				|| s[*i + 1] == '\t' || !ft_isalnum(s[*i + 1]))
				break ;
			(*i)++;
		}
		*ret = ft_strjoin(*ret, get_env(env, tmp));
	}
	else
		*ret = ft_strjoin_characters(*ret, s[*i]);
}

void	generate_error(t_lex *s)
{
	int	i;

	i = 0;
	while (s)
	{
		if (s->type == COMMAND)
			i = 1;
		if (!s->prev && !ft_strncmp(s->str, "<", ft_strlen("<")))
			generate_error(s->next);
		else if (i == 0 && check_if_operator(s->str))
		{
			printf("minishell : syntax error\n");
		}
		else if (!s->next && check_if_operator(s->str))
			printf("minishell : syntax error\n");
		s = s->next;
	}
}

char	*expand_var(char *s, char **env)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			handle_single_quote(s, &i, &ret);
		else if (s[i] == '\"')
			handle_double_quote(s, &ret, env, &i);
		else if (s[i] == '$')
			handle_dollar(s, &i, &ret, env);
		else if (s[i] == '<')
			handle_heredoc(s, &i, &ret);
		else
			ret = ft_strjoin_characters(ret, s[i]);
		i++;
	}
	return (ret);
}

int	main(int c, char **v, char **env)
{
	t_lex	*lex;
	char	*input;

	lex = NULL;
	(void)c;
	(void)v;
	(void)env;
	while (1)
	{
		input = readline("minishell$>:");
		if (ft_strlen(input) > 0)
		{
			input[ft_strlen(input)] = '\0';
			add_history(input);
			input = expand_var(input, env);
			input = insert_spaces(input);
			// printf("input : %s\n", input);
			lex = lexer(input);
			assign_type(lex);
			manage_type(lex);
			generate_error(lex);
			print_list(lex);
			free(input);
			input = NULL;
		}
	}
	return (0);
}
