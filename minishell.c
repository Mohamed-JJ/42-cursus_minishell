/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/10 17:06:21 by mjarboua         ###   ########.fr       */
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
		if (h.s)
			free_string(&h.s);
		if (!input[h.i])
			break ;
	}
	return (lex);
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
	return (free(input), input = NULL, ret);
}

void	handle_env(char	*s, char **ret, char **env, int *i)
{
	char	*tmp;
	char	*holder;

	tmp = NULL;
	holder = NULL;
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
	*ret = ft_strjoin(*ret, holder, 1);
	free(tmp);
	tmp = NULL;
	holder = NULL;
}

void	handle_double_quote(char *s, char **ret, char **env, int *i)
{
	printf("%p\t%p\n", s, *ret);
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
	char	*holder;

	tmp = NULL;
	holder = NULL;
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
		holder = get_env(env, tmp);
		*ret = ft_strjoin(*ret, holder, 1);
		free(tmp);
		tmp = NULL;
		holder = NULL;
	}
	else
		*ret = ft_strjoin_characters(*ret, s[*i]);
}

int generate_error2(t_lex *s, int *i)
{
	if (s->type == COMMAND)
		*i = 1;
	else if (s->prev && s->type == PIPE && s->next)
		*i = 0;
	if (s->next && check_if_operator(s->str) && check_if_operator(s->next->str))
		return (printf("minishell : syntax error\n"), 1);
	else if (!s->prev && !ft_strncmp(s->str, "<", 1) && !s->next)
		return (printf("minishell : syntax error\n"), 1);
	else if (!s->prev && !ft_strncmp(s->str, ">", 1) && !s->next)
		return (printf("minishell : syntax error\n"), 1);
	else if (!s->next && check_if_operator(s->str))
		return (printf("minishell : syntax error\n"), 1);
	return (0);
}

int	generate_error(t_lex *s)
{
	int	i;

	i = 0;
	while (s)
	{
		if (generate_error2(s, &i))
			return (1);
		else if (!s->prev && !ft_strncmp(s->str, ">", 1) && s->next)
		{
			s = s->next;
			continue ;
		}
		else if (i == 0 && check_if_operator(s->str) && s->next)
		{
			s = s->next;
			continue ;
		}
		else if (!s->prev && !ft_strncmp(s->str, "<", 1) && s->next)
		{
			s = s->next;
			continue ;
		}
		s = s->next;
	}
	return (0);
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
	return (free(s), s = NULL, ret);
}

void	check_arr(char **r)
{
	if (!r[0])
		r[0] = ft_strdup("");
	if (!r[1])
		r[1] = ft_strdup("");
	if (!r[2])
		r[2] = ft_strdup("");
	if (!r[3])
		r[3] = ft_strdup("");
}

void	fill_array(char **ret, int type, char *s)
{
	if (type == ARGUMENT)
	{
		ret[0] = ft_strjoin(ret[0], s, 0);
		ret[0] = ft_strjoin(ret[0], " ", 0);
	}
	else if (type == OUT_FILE)
	{
		ret[1] = ft_strjoin(ret[1], s, 0);
		ret[1] = ft_strjoin(ret[1], " ", 0);
	}
	else if (type == IN_FILE)
	{
		ret[2] = ft_strjoin(ret[2], s, 0);
		ret[2] = ft_strjoin(ret[2], " ", 0);
	}
	else if (type == HEREDOC_DEL)
	{
		ret[3] = ft_strjoin(ret[3], s, 0);
		ret[3] = ft_strjoin(ret[3], " ", 0);
	}
	check_arr(ret);
}

char	**create_arrays_of_files(t_lex *s)
{
	char	**ret;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	ret = malloc(sizeof(char *) * 5);
	while (i < 4)
	{
		ret[i] = NULL;
		i++;
	}
	while (s && s->type != PIPE)
	{
		fill_array(ret, s->type, s->str);
		s = s->next;
	}
	ret[4] = NULL;
	return (ret);
}

char	**empty_array()
{
	int		i;
	char	**files;

	files = malloc(sizeof(char *) * 5);
	i = 0;
	while (i <= 4)
	{
		files[i] = NULL;
		i++;
	}
	return (files);
}

void	fill_arrays(char *ar, char ***cpy)
{
	int		i;

	i = 0;
	if (!ar || ft_strlen(ar) == 0)
		*cpy = NULL;
	else
		*cpy = ft_split(ar, ' ');
}

t_cmd	*new_command(t_data *p)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd ));
	if (!ret)
		return (NULL);
	ret->command = ft_strdup(p->s);
	fill_arrays(p->arr[0], &ret->args);
	fill_arrays(p->arr[1], &ret->outfile);
	fill_arrays(p->arr[2], &ret->infile);
	fill_arrays(p->arr[3], &ret->heredoc_del);
	ret->in_out = p->i;
	return (ret);
}

void ft_lstadd_back_cmd(t_cmd **c, t_cmd *new)
{
	t_cmd	*tmp;

	if (!c)
		return ;
	if (!*c)
	{
		*c = new;
		return ;
	}
	tmp = *c;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	redirection_type(int type, t_data *d)
{
	if (type == REDIRECT)
		d->i = TO_BE_REDIRECTED;
	else if (type == APPEND)
		d->i = TO_BE_APPENDED;
}

void	join_string(char *str, char **string)
{
	*string = ft_strjoin(*string, str, 0);
	*string = ft_strjoin(*string, " ", 0);
}

t_cmd	*create_cmd(t_lex *s)
{
	t_cmd	*ret;
	t_data	d;

	d.i = 0;
	ret = NULL;
	while (s)
	{
		d.arr = empty_array();
		redirection_type(s->type, &d);
		if (s->type == COMMAND)
			d.s = ft_strdup(s->str);
		if (s->type == ARGUMENT)
			join_string(s->str, &d.arr[0]);
		else if (s->type == OUT_FILE)
			join_string(s->str, &d.arr[1]);
		else if (s->type == IN_FILE)
			join_string(s->str, &d.arr[2]);
		else if (s->type == HEREDOC_DEL)
			join_string(s->str, &d.arr[3]);
		else if (s->type == PIPE)
		{
			t_cmd *tmp = new_command(&d);
			ft_lstadd_back_cmd(&ret, tmp);
			int i  = 0;
			while (d.arr[i])
			{
				free(d.arr[i]);
				d.arr[i] = NULL;
				i++;
			}
			d.arr = NULL;
		}
		s = s->next;
	}
	ft_lstadd_back(&ret, new_command(&d));
	return (ret);
}

int	main(int c, char **v, char **env) // still need to pass the linked list of env variables becuz the user might set up new variables and might not find them in the env since the minishell is a running process
{
	t_lex	*lex;
	char	*input;
	// t_cmd	*cmd;

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
			lex = lexer(input);
			assign_type(lex);
			manage_type(lex);
			if (generate_error(lex))
			{
				while (lex)
				{
					free(lex->str);
					free(lex);
					lex = lex->next;
				}
			}
			else
				print_list(lex);
			while (lex)
			{
				free(lex->str);
				free(lex);
				lex = lex->next;
			}
		}
		free(input);
		input = NULL;
	}
	return (0);
}
