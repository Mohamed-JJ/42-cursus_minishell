/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:38:38 by mjarboua          #+#    #+#             */
/*   Updated: 2023/03/24 15:38:59 by mjarboua         ###   ########.fr       */
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