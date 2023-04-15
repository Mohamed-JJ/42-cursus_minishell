/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:39:11 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/15 21:29:46 by mjarboua         ###   ########.fr       */
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

enum e_type
{
	PIPE,
	COMMAND,
	REDIRECT,
	APPEND,
	HEREDOC,
	READ_INPUT,
	OUT_FILE,
	IN_FILE,
	WORD,
	HEREDOC_DEL,
	SPACE
};

t_env	*lst_new_env(char *arr, char *name);
void	ft_lstadd_back_env(t_env **alst, t_env *new);

t_exp	*lst_new_exp(char *arr);
void	ft_lstadd_back_exp(t_exp **alst, t_exp *new);

void	ft_lstadd_back(t_cmd **lst, t_cmd *new);
void	ft_lstadd_back_expander(t_exp **lst, t_exp *new);
t_cmd	*ft_lstnew(char	**content, int type);
t_exp	*new_exp(char **str);

char	**ft_split(char *s, char c);
char	*ft_strdup(char *str);
char	*ft_strchr(char *s, int c);
int		ft_strlen(char *str);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
char	*ft_strjoin_characters(char *s1, char c);
int		ft_isprint(int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
int		ft_strcmp(char *s1, char *s2);
int		check_if_operator(char *str);
int		skip_special_characters(char *str, int *i, char c);
void	dqoute_handler(char *str, t_data *data, t_lex **lex);
void	dqoute_handler_expander(char *str, t_data *data);

int		arr_len(char **arr);

#endif