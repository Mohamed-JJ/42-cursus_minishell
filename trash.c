/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:38:38 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/04 15:00:28 by mjarboua         ###   ########.fr       */
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
