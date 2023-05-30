/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:02:29 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/30 18:32:07 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include <stdio.h>

void	manage_type(t_lex *p)
{
	t_lex	*tmp;

	tmp = p;
	while (p)
	{
		handle_until_pipe(p);
		p = p->next;
	}
	tmp = p;
}

void	handle_until_pipe(t_lex *p)
{
	int	i;

	i = 0;
	while (p && p->type != PIPE)
	{
		if (p->type == WORD && !i)
		{
			p->type = COMMAND;
			i = 1;
		}
		else if (p->type == WORD)
			p->type = ARGUMENT;
		else if ((p->type == REDIRECT || p->type == APPEND) && p->next != NULL
			&& p->next->type == WORD)
			p->next->type = OUT_FILE;
		else if (p->type == READ_INPUT && p->next && p->next->type == WORD)
			p->next->type = IN_FILE;
		else if (p->type == HEREDOC && p->next->type == WORD)
			p->next->type = HEREDOC_DEL;
		p = p->next;
	}
}

void	assign_type(t_lex *p)
{
	int		i;
	t_lex	*tmp;

	tmp = p;
	i = 0;
	while (p)
	{
		if (!ft_strcmp("|", p->str) && !p->ds_quote)
			p->type = PIPE;
		else if (!ft_strcmp(">", p->str) && !p->ds_quote)
			p->type = REDIRECT;
		else if (!ft_strcmp(">>", p->str) && !p->ds_quote)
			p->type = APPEND;
		else if (!ft_strcmp("<", p->str) && !p->ds_quote)
			p->type = READ_INPUT;
		else if (!ft_strcmp("<<", p->str) && !p->ds_quote)
			p->type = HEREDOC;
		else
			p->type = WORD;
		p = p->next;
	}
	p = tmp;
}

void	continue_lexing(t_data *h, t_lex **lex, char *input)
{
	if (!input[h->i])
		return ;
	while (input[h->i] != ' ' && input[h->i] != '\t' && input[h->i])
	{
		if (input[h->i] == '\'' || input[h->i] == '\"')
			dqoute_handler(input, h, lex, 0);
		else
			h->s = ft_strjoin_parsing_characters(h->s, input[h->i++]);
		if (!input[h->i])
			break ;
	}
	if (!h->j)
		ft_lstadd_back_lexer(lex, new_lex(h->s, WORD, 0));
}

t_lex	*lexer(char *input)
{
	t_data	h;
	t_lex	*lex;

	h.i = -1;
	lex = NULL;
	h.s = NULL;
	while (input[++h.i])
	{
		h.j = 0;
		if (input[(h.i)] == '\'' || input[h.i] == '\"')
			dqoute_handler(input, &h, &lex, 1);
		if (input[h.i] && (input[h.i] == ' ' || input[h.i] == '\t'))
			skip_whitespaces(input, &h.i);
		if (input[h.i] && input[h.i] != ' ' && input[h.i] != '\t')
			continue_lexing(&h, &lex, input);
		if (h.s)
			free_string(&h.s);
		if (!input[h.i])
			break ;
	}
	return (lex);
}
