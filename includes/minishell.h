/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:39:11 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/17 12:54:57 by mjarboua         ###   ########.fr       */
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
# include "lexer.h"
# include "structs.h"
# include "utils.h"
# include <curses.h>
# include <term.h>

// lexer functions
int		check_if_operator(char *str);
void	dqoute_handler(char *str, t_data *data, t_lex **lex, int i);

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
int		handle_single_quote(char *s, int *i, char **ret);
int		handle_double_quote(char *s, char **ret, char **env, int *i);
void	handle_env(char	*s, char **ret, char **env, int *i);

// variable expansion functions
char	*get_env(char **env, char *s);
void	print_list(t_lex *lex);

// free functions
void	free_cmd_list(t_cmd *cmd);
void	free_list(t_lex	**list);
void	free_array(char **arr);


#endif