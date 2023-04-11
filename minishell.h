/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:39:11 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/11 15:05:31 by mjarboua         ###   ########.fr       */
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

typedef struct l_cmd
{
	char			*cmd;
	char			**args;
	int				p;
	char			*in_file;
	char			*out_file;
	int				r_in;
	int				app;
	int				heredoc;
	struct l_cmd	*next;
}			t_cmd;

void	ft_lstadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstnew(char	**content, int type);

/*-----------------------------------------------------*/

/*						utils functions					*/

char	**ft_split(char *s, char c);
char	*ft_strdup(char *str);
char	*ft_strchr(char *s, int c);
int		ft_strlen(char *str);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
char	*ft_strjoin_characters(char *s1, char c);
int		ft_isprint(int c);
char	*ft_substr(char *s, int start, int len);
int		ft_strcmp(char *s1, char *s2);
int		check_if_operator(char *str);
int		skip_special_characters(char *str, int *i, char c);


#endif