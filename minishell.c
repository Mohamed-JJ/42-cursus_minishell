/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/26 16:01:50 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else
		{
			while (input[h.i] == ' ' || input[h.i] == '\t')
				h.i++;
			while (input[h.i] != ' ' && input[h.i] != '\t' && input[h.i])
				h.s = ft_strjoin_characters(h.s, input[h.i++]);
			ft_lstadd_back_lexer(&lex, new_lex(h.s, WORD));
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
		else if (!ft_strcmp(">", p->str))
			p->type = REDIRECT;
		else if (!ft_strcmp(">>", p->str))
			p->type = APPEND;
		else if (!ft_strcmp("<", p->str))
			p->type = READ_INPUT;
		else if (!ft_strcmp("<<", p->str))
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
			character = input[i++];
			while (input[i] != character && input[i])
				ret = ft_strjoin_characters(ret, input[i++]);
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

// t_cmd	*syntax_analyzer(t_lex *p)
// {
// 	int		i;
// 	t_cmd	*cmd;

// 	cmd = NULL;
// 	i = 0;
// 	while (p)
// 	{
// 		if (i == 0 && p->type != COMMAND)
// 			return (printf("minishell : syntax error\n"), NULL);
// 		else if (i == 0 && p->type == COMMAND)
// 			i = 1;
// 		else if (p->type == PIPE)
// 			i = 0;
// 		p = p->next;
// 	}
// 	cmd = create_cmd(p);
// 	return (cmd);
// }

char	*get_env_var(char *var, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!var)
		return (NULL);
	while (env[i])
	{
		tmp = ft_substr(env[i], 0, ft_strlen(var));
		if (!ft_strncmp(tmp, var, ft_strlen(var)))
		{
			free(tmp);
			return (env[i] + ft_strlen(var) + 1);
		}
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (NULL);
}

void	handle_single_qoute_case(char *s, int *i, char **ret)
{
	(*i)++;
	while (s[*i] != '\'' && s[*i])
		*ret = ft_strjoin_characters(*ret, s[(*i)++]);
	if (!s[*i])
		printf("minishell : error in quotation\n");
	(*i)++;
}
void	handle_double_quote_case(char *s, int *i, char **ret, char **env)
{
	char	*tmp;
	int		f;

	tmp = NULL;
	f = 0;
	(*i)++;
	while (s[*i] != '\"' && s[*i])
	{
		if (s[*i] == '$' && s[*i + 1] != ' ' && s[*i + 1] != '\"')
		{
			(*i)++;
			f = *i;
			while (s[*i] != ' ' && s[*i] != '\t' && s[*i] != '\"' && s[*i])
				(*i)++;
			if (!s[*i])
				printf("minishell : error in quotation [end of line]\n");
			tmp = ft_substr(s, f, *i - f);
			*ret = ft_strjoin(*ret, get_env_var(tmp, env));
			// *ret = ft_strjoin(*ret, get_env_var(tmp, env));
			printf("%s\n", *ret);
		}
		else
			*ret = ft_strjoin_characters(*ret, s[*i]);
		(*i)++;
	}
	(*i)++;
	if (s[*i] == '\"')
		handle_double_quote_case(s, i, ret, env);
}

char	*expand_var(char *s, char **env)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = 0;
	(void)env;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			handle_single_qoute_case(s, &i, &ret);
			printf("%s\n", ret);
			exit(0);
		}
		else if(s[i] == '\"')
			handle_double_quote_case(s, &i, &ret, env);
		// else if (s[i] == '$')
		// 	ret = handle_dollar_case(s, &i, &ret, env);
		// else
		// 	ret = ft_strjoin_characters(ret, s[i]);
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
	while (1)
	{
		input = readline("minishell$>:");
		if (ft_strlen(input) > 0)
			input[ft_strlen(input)] = '\0';
		add_history(input);
		input = expand_var(input, env);
		free(input);
		input = NULL;
	}
	return (0);
}
