/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:25:04 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/17 13:49:05 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "structs.h"

t_lex	*new_lex(char *str, int type, int flag);
void	ft_lstadd_back_lexer(t_lex	**lst, t_lex *new);
t_lex	*ft_lstlast_lexer(t_lex *lst);

t_lex	*lexer(char *input);


// t_lex	*new_lex(char *str, int type);
void	ft_lstadd_back_lexer(t_lex	**lst, t_lex *new);
t_lex	*ft_lstlast_lexer(t_lex *lst);
void	check_rest_type(t_lex *p, int *i);
void	assign_type(t_lex *p);
void	handle_until_pipe(t_lex *p);
void	manage_type(t_lex *p);
void	manage_type(t_lex *p);

// cmd functions

t_cmd	*new_command(char *str, char **arr, int i);
void	ft_lstadd_back_cmd(t_cmd **c, t_cmd *new);
t_cmd	*fill_till_eol_pipe(char **str, char **arr, t_lex **s);
t_cmd	*create_cmd(t_lex *s);

#endif