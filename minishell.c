/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/12 22:05:10 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			dqoute_handler(input, &h, &lex);
		else
		{
			while (input[h.i] == ' ' || input[h.i] == '\t')
				h.i++;
			while (input[h.i] != ' ' && input[h.i] != '\t' && input[h.i])
			{
				h.s = ft_strjoin_characters(h.s, input[h.i]);
				h.i++;
			}
			ft_lstadd_back_lexer(&lex, new_lex(h.s, WORD));
		}
		free(h.s);
		h.s = NULL;
		if (!input[h.i])
			break ;
	}
	return (lex);
}

void	assign_type(t_lex *p)
{
	int		i;
	t_lex	*tmp;

	tmp = p;
	i = 0;
	while (p)
	{
		if (!ft_strcmp(">", p->str))
			p->type = REDIRECT;
		else if (!ft_strcmp(">>", p->str))
			p->type = APPEND;
		else if (!ft_strcmp("<", p->str))
		{
			p->prev->type = IN_FILE;
			p->type = READ_INPUT;
		}
		else if (!ft_strcmp("<<", p->str))
			p->type = HEREDOC;
		else
			check_rest_type(p, &i);
		p = p->next;
	}
	p = tmp;
}

char	*insert_spaces(char *input)
{
	int		i;
	char	*ret;
	char	character;

	i = -1;
	ret = NULL;
	while (input[++i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			character = input[i];
			ret = ft_strjoin_characters(ret, ' ');
			while (input[i] == character && input[i])
			{
				if (input[i + 1] != character)
					break ;
				ret = ft_strjoin_characters(ret, input[i++]);
			}
			ret = ft_strjoin_characters(ret, input[i]);
			ret = ft_strjoin_characters(ret, ' ');
		}
		else
			ret = ft_strjoin_characters(ret, input[i]);
	}
	return (ret);
}

void	print_list(t_lex *lex)
{
	while (lex)
	{
		if (lex->type == COMMAND)
			printf("%s is a command\n", lex->str);
		else if (lex->type == PIPE)
			printf("%s is a pipe\n", lex->str);
		else if (lex->type == REDIRECT)
			printf("%s is a redirect\n", lex->str);
		else if (lex->type == HEREDOC)
			printf("%s is a heredoc\n", lex->str);
		else if (lex->type == APPEND)
			printf("%s is a append\n", lex->str);
		else if (lex->type == IN_FILE)
			printf("%s is a input file\n", lex->str);
		else if (lex->type == OUT_FILE)
			printf("%s is a output file\n", lex->str);
		else if (lex->type == READ_INPUT)
			printf("%s is a read input\n", lex->str);
		else if (lex->type == HEREDOC_DEL)
			printf("%s is a heredoc delimiter\n", lex->str);
		else
			printf("%s is an argument\n", lex->str);
		lex = lex->next;
	}
}

t_exp	*store_var(char *input)
{
	char	**var;
	t_exp *p;
	t_data h;

	h.i = 0;
	h.s = NULL;
	p = NULL;
	while (input[h.i])
	{
		if (input[h.i] == '=')
		{
			while (input[h.i] != ' ' && input[h.i] != '\t' && input[h.i])
				h.i--;
			while (input[h.i] != '=' && input[h.i])
			{
				h.s = ft_strjoin_characters(h.s, input[h.i]);
				h.i++;
			}
			
		}
	}
	// in this function we will store the variables in a linked list of local variables
	// and we will need a function that gets the value of the variable invoked in the input to replace it
}

int	main(void)
{
	t_lex	*lex;
	t_exp	*exp;
	char	*input;

	while (1)
	{
		input = readline("minimlawi$>:");
		if (ft_strlen(input) > 0)
			input[ft_strlen(input)] = '\0';
		add_history(input);
		exp = expand_var(input);
		input = insert_spaces(input);
		lex = lexer(input);
		assign_type(lex);
	}
}
