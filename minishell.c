/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/05 22:24:55 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct l_var
{
	int		i;
	int		j;
	int		x;
}		t_var;

char	*string_with_spaces(char *string, int i, int counter)
{
	int		f;
	int		x;
	char	*ret;

	x = 0;
	f = 0;
	ret = malloc(i + counter + 1);
	while (string[x])
	{
		if (string[x] == '|' || string[x] == '>' || string[x] == '<')
		{
			ret[f++] = ' ';
			while (string[x] == '|' || string[x] == '>' || string[x] == '<')
				ret[f++] = string[x++];
			ret[f++] = ' ';
			ret[f] = string[x];
		}
		else
			ret[f] = string[x];
		f++;
		x++;
	}
	ret[f] = '\0';
	return (ret);
}

char	*expanded_string(char *str)
{
	int		i;
	int		counter;
	char	*ret;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			counter += 2;
			while (str[i] == '|' && str[i] == '<' && str[i] == '>')
				i++;
		}
		i++;
	}
	ret = string_with_spaces(str, i, counter);
	return (ret);
}

void	do_change(char *c, int character)
{
	if (*c == character)
		*c = '\t';
}

void	handle_what_inside_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
			while (str[++i] != 39)
				do_change(&str[i], ' ');
		else if (str[i] == 34)
			while (str[++i] != 34)
				do_change(&str[i], ' ');
		i++;
	}
}

char	*handle_qoutes(char *input, int *i)
{
	int		s;
	int		e;

	s = 0;
	e = 0;
	if (input[*i] == '\"')
	{
		s = *i;
		while (input[++*i])
			if (input[*i] == '\"')
				return (ft_substr(input, s, *i - s + 1));

	}
	else if (input[*i] == '\'')
	{
		s = *i;
		while (input[++*i])
			if (input[*i] == '\'')
				return (ft_substr(input, s, *i - s + 1));
	}
	else
	{
		while (input[*i] && input[*i] != ' ')
			(*i)++;
		return (ft_substr(input, s, *i - s));
	}
	return (NULL);
}

// void	lexer(char *input)
// {
// 	int		i;
// 	char	*joined;

// 	i = -1;
// 	while (input[++i])
// 	{
// 		if (input[i] == ' ')
// 			continue ;
// 		else if (input[i] == '\"' || input[i] == '\'')
// 			handle_qoutes(input, &i);
// 		else
// 			handle_qoutes(input, &i);
// 	}
// }

int	check_if_operator(char *str)
{
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<<") == 0 || ft_strcmp(str, "||") == 0
		|| ft_strcmp(str, "&&") == 0)
		return (1);
	return (0);
}

char	*extract_from_quote(char *str, int *iter, char quote)
{
	int		i;
	char	*ret;

	i = *iter;
	ret = NULL;
	while (str[i] && str[i] != quote)
	{
		ret = ft_strjoin(ret, str[i]);
		i++;
	}
	return (ret);
}

t_lex	*lexer(char *input)
{
	char	*holder;
	t_lex	*lex;
	int		i;

	i = 0;
	lex = NULL;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			holder = extract_from_quote(input, &i, '\'');
			ft_lstadd_back(&lex, ft_lstnew(holder, WORD));
		}
		else if (input[i] == '\"')
		{
			holder = extract_from_quote(input, &i, '\'');
			ft_lstadd_back(&lex, ft_lstnew(holder, WORD));
		}
	}
	return (lex);
}

int	main(int c, char **v, char **env)
{
	t_lex	*lex;

	(void)c;
	(void)v;
	(void)env;
	while (1)
	{
		input = readline("minimlawi$>:");
		if (ft_strlen(input) > 0)
			input[ft_strlen(input)] = '\0';
		add_history(input);
		handle_what_inside_quote(input);
		lex = lexer(input);
		while (lex)
		{
			if (!lex->op)
				printf("%s and its type is literal\n\n", lex->str);
			else
				printf("%s and it's type is operator\n\n", lex->str);
			lex = lex->next;
		}
	}
}

// you consider making your delimiter a redirection
// of any type and pipe operators or the and operator

// first we should work on orgainzing our commands and their arguments and manage the redirections and pipes
// as soon as we find a redirection or a pipe we should split the string into part according to how many redirections and pipes we have