/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/03/22 19:13:14 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define out 0

int	is_op(char *str)
{
	int		i;
	char	*ops;

	i = 0;
	ops = ft_strdup("|><");
	while (str[i])
	{
		if (ft_strchr(ops, str[i]))
			return (free(ops), 1);
		i++;
	}
	return (free(ops), 0);
}

t_input	*lex_input(char **str)
{
	t_input	*ret;
	int		i;

	ret = NULL;
	i = 0;
	while (str[i])
	{
		if (is_op(str[i]))
			ft_lstadd_back(&ret, ft_lstnew(str[i], 1));
		else
			ft_lstadd_back(&ret, ft_lstnew(str[i], 0));
		i++;
	}
	return (ret);
}

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
		printf("%d\n", (int)str[i]);
		if (str[i] == 39)
		{
			i++;
			while (str[i] != 39)
			{
				do_change(&str[i], ' ');
				i++;
			}
		}
		else if (str[i] == 34)
		{
			i++;
			while (str[i] != 34)
			{
				do_change(&str[i], ' ');
				i++;
			}
		}
		i++;
	}
}

// void	commence(char *v)
// {
// 	t_input	*d;
// 	char	*str;
// 	char	**arr;

// 	str = expanded_string(v);
// 	// if (check_double_quotes(str) == 1)
// 	str = handle_what_inside_quote(str);
// 	return ((void)printf("%s\n", str));
// 	arr = ft_split(str, ' ');
// 	d = lex_input(arr);
// }

int	main(int c, char **v, char **env)
{
	char	*input =ft_strdup("hello kjhsfg \"svjdlvrjlhgaos oieagr\"");
	// char	*history;

	(void)c;
	(void)v;
	(void)env;
	printf("%s\n", input);
	handle_what_inside_quote(input);
	printf("%s\n", input);
	// while (1)
	// {
	// 	input = readline("mini9lawi$>:");
	// 	read_history(history);
	// 	commence(input);	
	// }
	return (0);
}
