/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:44:53 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/30 17:26:58 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
	ARGUMENT
};

enum e_status
{
	TO_BE_PIPED,
	TO_BE_EXECUTED,
	TO_BE_REDIRECTED,
	TO_BE_APPENDED,
	TO_BE_HEREDOC,
	TO_BE_READ_INPUT,
	END_OF_LINE,
};

enum e_exc
{
	MANUAL,
	AUTO,
};

typedef struct l_data
{
	int		i;
	int		j;
	char	c;
	char	*s;
	char	**arr;
}		t_data;

typedef struct l_lex
{
	char			*str;
	int				type;
	int				ds_quote;
	struct l_lex	*next;
	struct l_lex	*prev;
}		t_lex;

typedef struct l_env
{
	char			*value;
	char			*name;
	struct l_env	*next;
}			t_env;

typedef struct l_cmd
{
	char			*command;
	char			**args;
	int				is_red_or_app;
	int				in_out;
	int				fd_in;
	int				h_i;
	char			**infile;
	char			**outfile;
	char			**heredoc_del;
	struct l_cmd	*next;
}			t_cmd;

typedef struct exe_fd
{
	int	fd2[2];
	int	fd1[2];
	int	fd_in;
	int	fd_out;
	int	outfile;
	int	fd_heredoc;
	int	out;
	int	in;
	int	pid;
}		t_exe_fd;

#endif