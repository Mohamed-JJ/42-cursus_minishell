/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 21:49:16 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/21 16:02:32 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

// utils functions

void	free_string(char **lex);
void	free_array(char **lex);
int		arr_len(char **arr);
char	*expand_var(char *s, t_env *env);
void	skip_whitespaces(char *str, int *i);
int		skip_special_characters(char *str, int *i, char c);
char	**empty_array(void);
char	**fill_arrays(char *ar);
void	fill_array(char **ret, int type, char *s);
char	*join_string(char *str, char **string);
char	**create_arrays_of_files(t_lex *s);
void	check_arr(char **r);
int		generate_error2(t_lex *s, int *i);
int		generate_error(t_lex *s);
void	redirection_type(int type, int *d);

#endif