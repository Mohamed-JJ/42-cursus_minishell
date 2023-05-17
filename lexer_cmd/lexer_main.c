/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:02:29 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/17 19:20:51 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

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
	int		i;

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
		else if ((p->type == REDIRECT || p->type == APPEND)
			&& p->next != NULL && p->next->type == WORD)
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
		if (!ft_strcmp("|", p->str))
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

void	check_rest_type(t_lex *p, int *i)
{
	printf("active\n");
	if (p->type == APPEND)
	{
		p->next->type = OUT_FILE;
	}
	else if (!ft_strcmp("|", p->str))
	{
		*i = 0;
		p->type = PIPE;
	}
	else if (p->type == WORD && (!(*i) || !p->prev))
	{
		*i = 1;
		p->type = COMMAND;
	}
	else if (p->prev->type == REDIRECT && p->type)
		p->type = OUT_FILE;
	else if (p->prev->type == HEREDOC)
		p->type = HEREDOC_DEL;
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
		if (input[(h.i)] == '\'' || input[h.i] == '\"')
			dqoute_handler(input, &h, &lex, 1);
		if (input[h.i] && (input[h.i] == ' ' || input[h.i] == '\t'))
			skip_whitespaces(input, &h.i);
		else if (input[h.i] && input[h.i] != ' ' && input[h.i] != '\t')
		{
			while (input[h.i] != ' ' && input[h.i] != '\t' && input[h.i])
			{
				if (input[h.i] == '\'' || input[h.i] == '\"')
					dqoute_handler(input, &h, &lex, 0);
				else if (input[h.i] == '=' && (input[h.i + 1] == '\'' || input[h.i + 1] == '\"'))
				{
					h.s = ft_strjoin_parsing_characters(h.s, input[h.i++]);
					dqoute_handler(input, &h, &lex, 0);
				}
				else
				h.s = ft_strjoin_parsing_characters(h.s, input[h.i++]);
			}
			ft_lstadd_back_lexer(&lex, new_lex(h.s, WORD, 0));
		}
		free_string(&h.s);
		if (!input[h.i])
			break ;
	}
	return (lex);
}
