/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:39:11 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/10 21:46:51 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lexer/lexer.h"
# include "structs.h"
# include <curses.h>
# include <term.h>

// lexer functions
int		check_if_operator(char *str);
void	dqoute_handler(char *str, t_data *data, t_lex **lex);

// string functions
char	**ft_split(char *s, char c);
char	*ft_strdup(char *str);
int		ft_strchr(char *s, int c);
int		ft_strlen(char *str);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
char	*ft_strjoin_characters(char *s1, char c);
int		ft_isprint(int c);
char	*ft_strjoin(char *s1, char *s2, int _free);
char	*ft_substr(char *s, int start, int len);
int		ft_isalnum(int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// case managment functions
void	handle_heredoc(char *s, int *i, char **ret);
void	handle_dollar(char *s, int *i, char **ret, char **env);
void	handle_single_quote(char *s, int *i, char **ret);
void	handle_double_quote(char *s, char **ret, char **env, int *i);
void	handle_env(char	*s, char **ret, char **env, int *i);

// variable expansion functions
char	*get_env(char **env, char *s);


void	print_list(t_lex *lex);

// utils functions
void	free_string(char **lex);
void	free_array(char ***lex);
int		arr_len(char **arr);
char	*expand_var(char *s, char **env);
void	skip_whitespaces(char *str, int *i);
int		skip_special_characters(char *str, int *i, char c);
char	**empty_array(void);
void	fill_arrays(char *ar, char ***cpy);
void	fill_array(char **ret, int type, char *s);
void	join_string(char *str, char **string);
char	**create_arrays_of_files(t_lex *s);
void	check_arr(char **r);
int		generate_error2(t_lex *s, int *i);
int		generate_error(t_lex *s);
void	redirection_type(int type, t_data *d);

#endif