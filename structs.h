/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:44:53 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/16 15:31:49 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

enum e_status
{
	TO_BE_PIPED,
	TO_BE_EXECUTED,
	TO_BE_REDIRECTED,
	TO_BE_APPENDED,
	TO_BE_HEREDOC,
	TO_BE_READ_INPUT
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
	char			*name;
	char			*s;
	struct l_exp	*next;
}			t_exp;

typedef struct l_cmd
{
	char			*cmd;
	char			**args;
	int				status;
	int				type;
	char			*heredoc;
	char			*infile;
	char			*outfile;
	struct l_cmd	*next;
}			t_cmd;

#endif