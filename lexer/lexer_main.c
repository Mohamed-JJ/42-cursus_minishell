/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:02:29 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/18 16:03:26 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	check_rest_type(t_lex *p, int *i)
{
	if (p->type == APPEND)
		p->next->type = OUT_FILE;
	else if (!ft_strcmp("|", p->str))
	{
		*i = 0;
		p->type = PIPE;
	}
	else if (p->type == WORD && (!(*i) || !p->prev))
	{
		*i = 1;
		p->type = COMMAND;
	}
	else if (p->prev->type == REDIRECT)
		p->type = OUT_FILE;
	else if (p->prev->type == HEREDOC)
		p->type = HEREDOC_DEL;
}