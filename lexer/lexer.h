/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:25:04 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/11 16:51:33 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "../minishell.h"

typedef struct l_lex
{
	char			*str;
	int				type;
	struct l_lex	*next;
	struct l_lex	*prev;
}		t_lex;

t_lex	*new_lex(char *str, int type);
void	ft_lstadd_back_lexer(t_lex	**lst, t_lex *new);
t_lex	*ft_lstlast_lexer(t_lex *lst);

t_lex	*new_lex(char *str, int type);
void	ft_lstadd_back_lexer(t_lex	**lst, t_lex *new);
t_lex	*ft_lstlast_lexer(t_lex *lst);
void	check_rest_type(t_lex *p, int *i);

#endif