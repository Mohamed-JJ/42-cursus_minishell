/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:40:55 by mjarboua          #+#    #+#             */
/*   Updated: 2023/02/16 14:56:29 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exp	*ft_lstnew(char *content)
{
	t_exp	*new;

	new = malloc(sizeof(t_exp));
	if (!new)
		return (NULL);
	new->v = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_exp **lst, t_exp *new)
{
	t_exp	*node;

	node = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

void	ft_lstadd_front(t_exp **lst, t_exp *new)
{	
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

t_exp	*ft_last_exp(t_exp *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

int	ft_lstsize(t_exp *d)
{
	int	i;

	i = 0;
	if (!d)
		return (0);
	while (d)
	{
		d = d->next;
		i++;
	}
	return (i);
}