/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:15:37 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/06 16:54:12 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex	*new_lex(char **str, int type)
{
	t_lex	*new;

	new = malloc(sizeof(t_lex));
	new->str = ft_strdup(*str);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	free(*str);
	*str = NULL;
	return (new);
}

void	ft_lstadd_back_lexer(t_lex	**lst, t_lex *new)
{
	t_lex	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_lex	*ft_lstlast_lexer(t_lex *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

