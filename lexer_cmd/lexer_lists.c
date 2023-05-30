/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:15:37 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/27 20:50:27 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/lexer.h"

t_lex	*new_lex(char *str, int type, int flag)
{
	t_lex	*new;

	new = malloc(sizeof(t_lex));
	new->str = ft_strdup_parsing(str);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	new->ds_quote = flag;
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
