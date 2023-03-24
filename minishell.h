/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:39:11 by mjarboua          #+#    #+#             */
/*   Updated: 2023/03/20 17:52:58 by mjarboua         ###   ########.fr       */
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

// typedef struct l_input
// {
// 	char			*str;
// 	int				literal;
// 	int				op;
// 	struct l_input	*next;
// }		t_input;

typedef struct l_cmd
{
	char			*cmd;
	char			**args;
	int				p;
	int				r_out;
	int				r_in;
	int				app;
	int				heredoc;
	struct l_cmd	*next;
}			t_cmd;

char	**ft_split(char *s, char c);
char	*ft_strdup(char *str);
char	*ft_strchr(char *s, int c);
int		ft_strlen(char *str);
int		ft_isdigit(int c);
int		ft_isalpha(int c);

void	ft_lstadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstnew(char	*content, int type);

int		ft_isprint(int c);
char	*ft_substr(char *s, int start, int len);

#endif