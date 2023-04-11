/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:02:29 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/11 17:10:59 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	check_rest_type(t_lex *p, int *i)
{
	if (!ft_strcmp("|", p->str))
	{
		*i = 0;
		p->type = PIPE;
	}
	else if (!(*i) || !p->prev)
	{
		*i = 1;
		p->type = COMMAND;
	}
	else if (p->prev->type == APPEND)
		p->type = OUT_FILE;
	else if (p->prev->type == REDIRECT)
		p->type = OUT_FILE;
	else if (p->prev->type == HEREDOC)
		p->type = HEREDOC_DEL;
}