/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:39:11 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/07 23:39:39 by mjarboua         ###   ########.fr       */
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

enum e_type
{
	PIPE,
	REDIRECT,
	APPEND,
	HEREDOC,
	COMMAND,
	ARGUMENT,
	READ_INPUT,
	OUTPUT_FILE,
	INPUT_FILE,
	HEREDOC_CONTENT,
	SPACE
};

/*          lexer related functions and data           */

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

/*          parser related functions and data          */

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

#endif