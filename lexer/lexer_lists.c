/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:15:37 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/16 21:08:57 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/lexer.h"

t_lex	*new_lex(char *str, int type, int flag)
{
	t_lex	*new;
	static int	i = 0;

	printf("the itteration is %d\n", i++);

	new = malloc(sizeof(t_lex));
	new->str = ft_strdup(str);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	new->ds_quote = flag;
	// free_string(&str);
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
	// free_string(tmp->str);
}

t_lex	*ft_lstlast_lexer(t_lex *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
