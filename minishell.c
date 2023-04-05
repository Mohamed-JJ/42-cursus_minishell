/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/05 15:44:49 by mjarboua         ###   ########.fr       */
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

void	lexer(char *input)
{
	int		i;
	char	*joined;

	i = -1;
	while (input[++i])
	{
		if (input[i] == ' ')
			continue ;
		else if (input[i] == '\"' || input[i] == '\'')
			handle_qoutes(input, &i);
		else
			handle_qoutes(input, &i);
	}
}

int	main(int c, char **v, char **env)
{
	char	*input;

	(void)c;
	(void)v;
	(void)env;
	while (1)
	{
		input = readline("minimlawi$>:");
		if (ft_strlen(input) > 0)
			input[ft_strlen(input)] = '\0';
		add_history(input);
		handle_qoutes(input, &i);
	}
	return (0);
}

// you consider making your delimiter a redirection
// of any type and pipe operators or the and operator

// first we should work on orgainzing our commands and their arguments and manage the redirections and pipes
// as soon as we find a redirection or a pipe we should split the string into part according to how many redirections and pipes we have