/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/28 21:21:02 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_lex	*lexer(char *input)
// {
// 	t_data	h;
// 	t_lex	*lex;

// 	h.i = -1;
// 	lex = NULL;
// 	h.s = NULL;
// 	while (input[++h.i])
// 	{
// 		if (input[(h.i)] == '\'' || input[h.i] == '\"')
// 			dqoute_handler(input, &h, &lex);
// 		else
// 		{
// 			while (input[h.i] == ' ' || input[h.i] == '\t')
// 				h.i++;
// 			while (input[h.i] != ' ' && input[h.i] != '\t' && input[h.i])
// 				h.s = ft_strjoin_characters(h.s, input[h.i++]);
// 			ft_lstadd_back_lexer(&lex, new_lex(h.s, WORD));
// 		}
// 		free(h.s);
// 		h.s = NULL;
// 		if (!input[h.i])
// 			break ;
// 	}
// 	return (lex);
// }

// void	assign_type(t_lex *p)
// {
// 	int		i;
// 	t_lex	*tmp;

// 	tmp = p;
// 	i = 0;
// 	while (p)
// 	{
// 		if (!ft_strcmp("|", p->str))
// 			p->type = PIPE;
// 		else if (!ft_strcmp(">", p->str))
// 			p->type = REDIRECT;
// 		else if (!ft_strcmp(">>", p->str))
// 			p->type = APPEND;
// 		else if (!ft_strcmp("<", p->str))
// 			p->type = READ_INPUT;
// 		else if (!ft_strcmp("<<", p->str))
// 			p->type = HEREDOC;
// 		else
// 			p->type = WORD;
// 		p = p->next;
// 	}
// 	p = tmp;
// }

// char	*insert_spaces(char *input)
// {
// 	int		i;
// 	char	*ret;
// 	char	character;

// 	i = -1;
// 	ret = NULL;
// 	while (input[++i])
// 	{
// 		if (input[i] == '\'' || input[i] == '\"')
// 		{
// 			character = input[i++];
// 			while (input[i] != character && input[i])
// 				ret = ft_strjoin_characters(ret, input[i++]);
// 		}
// 		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
// 		{
// 			character = input[i];
// 			ret = ft_strjoin_characters(ret, ' ');
// 			while (input[i] == character && input[i])
// 			{
// 				if (input[i + 1] != character)
// 					break ;
// 				ret = ft_strjoin_characters(ret, input[i++]);
// 			}
// 			ret = ft_strjoin_characters(ret, input[i]);
// 			ret = ft_strjoin_characters(ret, ' ');
// 		}
// 		else
// 			ret = ft_strjoin_characters(ret, input[i]);
// 	}
// 	return (ret);
// }

// void	handle_until_pipe(t_lex *p)
// {
// 	int		i;
// 	t_lex	*tmp;

// 	i = 0;
// 	tmp = p;
// 	while (p)
// 	{
// 		if (p->type == PIPE)
// 			break ;
// 		if (p->type == WORD && !i)
// 		{
// 			p->type = COMMAND;
// 			i = 1;
// 		}
// 		else if (p->type == WORD)
// 			p->type = ARGUMENT;
// 		else if ((p->type == REDIRECT || p->type == APPEND)
// 			&& p->next != NULL && p->next->type == WORD)
// 			p->next->type = OUT_FILE;
// 		else if (p->type == READ_INPUT && p->next && p->next->type == WORD)
// 			p->next->type = IN_FILE;
// 		else if (p->type == HEREDOC && p->next->type == WORD)
// 			p->next->type = HEREDOC_DEL;
// 		p = p->next;
// 	}
// }

// void	manage_type(t_lex *p)
// {
// 	t_lex	*tmp;

// 	tmp = p;
// 	while (p)
// 	{
// 		handle_until_pipe(p);
// 		p = p->next;
// 	}
// }

// // t_cmd	*syntax_analyzer(t_lex *p)
// // {
// // 	int		i;
// // 	t_cmd	*cmd;

// // 	cmd = NULL;
// // 	i = 0;
// // 	while (p)
// // 	{
// // 		if (i == 0 && p->type != COMMAND)
// // 			return (printf("minishell : syntax error\n"), NULL);
// // 		else if (i == 0 && p->type == COMMAND)
// // 			i = 1;
// // 		else if (p->type == PIPE)
// // 			i = 0;
// // 		p = p->next;
// // 	}
// // 	cmd = create_cmd(p);
// // 	return (cmd);
// // }

char	*get_env(char **env, char *s)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], s, ft_strlen(s)))
		{
			ret = ft_strdup(env[i] + ft_strlen(s) + 1);
			break ;
		}
		i++;
	}
	return (ret);
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
	printf("the character |%c|\n", s[*i]);
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
		printf("minishell : single quote not closed\n");
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
		printf("minishell : single quote not closed\n");
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
	while (s[*i])
	{
		if (ft_strchr("|><", s[*i]))
			break ;
		*ret = ft_strjoin_characters(*ret, s[*i]);
		(*i)++;
	}
}

void	handle_dollar(char *s, int *i, char **ret, char **env)
{
	char	*tmp;

	tmp = NULL;
	if (s[*i] == '$' && s[*i + 1] != ' ' && s[*i + 1] != '\t')
	{
		(*i)++;
		while (s[*i] && ft_isalnum(s[*i]))
		{
			tmp = ft_strjoin_characters(tmp, s[*i]);
			if (!s[*i + 1] || s[*i + 1] == ' ' || s[*i + 1] == '\t' || !ft_isalnum(s[*i + 1]))
				break ;
			(*i)++;
		}
		*ret = ft_strjoin(*ret, get_env(env, tmp));
		// printf("the string |%s|\n", *ret);
		// exit(0);
	}
	else
		*ret = ft_strjoin_characters(*ret, s[*i]);
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
	printf("%s\n", ret);
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
			input[ft_strlen(input)] = '\0';
		add_history(input);
		input = expand_var(input, env);
		free(input);
		input = NULL;
	}
	return (0);
}
