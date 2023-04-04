/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/04 22:40:54 by mjarboua         ###   ########.fr       */
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

char	*handle_qoutes(char *input)
{
	int		i;
	int		s;
	int		e;

	i = -1;
	s = 0;
	e = 0;
	if (input[i] == '\"')
	{
		while (input[++i]);

	}
	else if (input[i] == '\'')
	{
		while (input[++i])
		{
		}
	}
} // this function return to a anotheer function. this function is just a utility function, we pass a pointer to the string from the index
// we want to handle the double quotes inside and we return whats inside double quotes one after the other
// generate a function that 

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
		handle_qoutes(input);
	}
	return (0);
}

// you consider making your delimiter a redirection
// of any type and pipe operators or the and operator