/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/03/21 21:44:53 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	commence(char *v)
{

	t_input	*d;
	int		i;
	char	*str;
	char	**arr;

	i = 0;
	str = expanded_string(v);
	arr = ft_split(str, ' ');
	d = lex_input(arr);
	while (d)
	{
		if (d->literal == 1)
			printf("the token | %s | and its type is literal\n", d->str);
		else
			printf("the token | %s | type is operator\n", d->str);
		d = d->next;
	}
}

int	main(int c, char **v, char **env)
{
	(void)c;
	(void)v;
	(void)env;
	commence(v[1]);
	return (0);
}
