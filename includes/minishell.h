/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:39:11 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/19 19:25:20 by imaaitat         ###   ########.fr       */
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
# include "../libft/libft.h"
# include <curses.h>
# include <term.h>
int status;
// lexer functions
int		check_if_operator(char *str);
void	dqoute_handler(char *str, t_data *data, t_lex **lex, int i);

// string functions
char	**ft_split_parsing(char *s, char c);
char	*ft_strdup_parsing(char *str);
int		ft_strchr_parsing(char *s, int c);
int		ft_strlen_parsing(char *str);
int		ft_isdigit_parsing(int c);
int		ft_isalpha_parsing(int c);
char	*ft_strjoin_parsing_characters(char *s1, char c);
int		ft_isprint_parsing(int c);
char	*ft_strjoin_parsing(char *s1, char *s2, int _free);
char	*ft_substr_parsing(char *s, int start, int len);
int		ft_isalnum_parsing(int c);
// int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp_parsing(const char *s1, const char *s2, size_t n);

// case managment functions
void	handle_heredoc(char *s, int *i, char **ret);
void	handle_dollar(char *s, int *i, char **ret, char **env);
int		handle_single_quote(char *s, int *i, char **ret);
int		handle_double_quote(char *s, char **ret, char **env, int *i);
void	handle_env(char	*s, char **ret, char **env, int *i);

// variable expansion functions
char	*get_env(char **env, char *s);
//void	print_list(t_lex *lex);

// free functions
void	free_cmd_list(t_cmd *cmd);
void	free_list(t_lex	**list);
void	free_array(char **arr);

// inserting space functions
void	insert_space_inside_quotes(char *input, int *i, char **ret);
void	insert_space_between_op(char *input, int *i, char **ret);
char	*insert_spaces(char *input);

// -----------------------execution functions------------------
void execution(char *command,char **args);
int check_heredoc(char **del);
void    ft_cd(char *argv);
int ft_pwd(int fd);
void signal_handler(int signum);
int create_out_files(t_cmd *p_cmd);
int builtin_cmd(char *command, char **args, t_env **head);
int create_in_files(t_cmd *p_cmd);
int ft_echo(char **argv);
int ft_redirection(char **command, char *name_file);
char *ft_export(char *argv);
void print_env(t_env *env,int i);
void free_env(t_env *env);
t_env *sort_env(t_env **head);
t_env *set_env(char **env, t_env *head);
t_env *copy_env(t_env *head);
int chek_plus(char *str);
void serch_replace(t_env *head,char *name,char *value);
char *get_name(char *str);
char *get_value(char *str);
void delete_env(t_env *head, char *name);
void unset_env(char **args, t_env *head) ;
void execution1(t_env *headd,t_cmd *p_cmd, char **env);
void cp_arr(char **arr, char **arr1);

#endif