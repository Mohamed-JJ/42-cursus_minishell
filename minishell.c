/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/03/24 16:01:45 by mjarboua         ###   ########.fr       */
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

int	check_double_quotes(char *str)
{
	int	s;
	int	d;

	d = 0;
	s = 0;
	while (*str)
	{
		if (*str == '\'')
			s++;
		else if (*str == '\"')
			d++;
		str++;
	}
	if (d % 2 == 1 || s % 2 == 1)
		return (1);
	return (0);
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

t_cmd	*fill_list(char **str, int start, int end, int pipe)
{
	t_cmd	*h;
	int		i;

	i = 1;
	h->cmd = str[0];
	while (str[i])
	{
		if (in_out_red(str[i]))
		{
			handle_red(str, &i); // we need to handle the red in/out and i need to pass an address of the iterator in order to keep everything in order
		}
	}
	return (h);
}

t_cmd	*syntax_analyser(char **str)
{
	t_cmd	*h;
	int		i;
	int		s;

	i = -1;
	s = 0;
	while (str[++i])
	{
		if (is_pipe(str[i]))
		{
			h = fill_list(str, s, i, 1);
			s = i;
		}
		else if (is_pipe(str[i]) == -1)
			write(1, "syntax error\n", 14);
	}
	fill_list(str, s, i, 0);
	// check if a pipe is in the array. if its true fill the list until the pipe, else fill it regularly
	return (h);
}

void	commence(char *v)
{
	t_cmd	*h;
	char	*str;
	char	**arr;

	str = expanded_string(v);
	handle_what_inside_quote(str);
	arr = ft_split(str, ' ');
	free(str);
	h = syntax_analyser(arr);
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
		input[ft_strlen(input) - 1] = '\0';
		read_history(input);
		commence(input);
	}
	return (0);
}
