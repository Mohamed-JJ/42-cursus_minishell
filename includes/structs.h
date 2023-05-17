/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:44:53 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/17 14:36:04 by mjarboua         ###   ########.fr       */
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
	ARGUMENT,
	SPACE
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

typedef struct l_exp
{
	char			*value;
	char			*s;
	struct l_exp	*next;
}			t_exp;

typedef struct l_cmd
{
	char			*command;
	char			**args;
	int				in_out;
	int  		 	h_i;
	char			**infile;
	char			**outfile;
	char			**heredoc_del;
	struct l_cmd	*next;
}			t_cmd;

typedef struct l_col
{
	char			**args;
	char			*str;
	t_lex			*lex;
	t_cmd			*cmd;
	struct l_col	*next;
}			t_col;

#endif