/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/08 21:05:28 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct l_data
{
	char		c;
	char		*s;
	int			i;
	int			j;
}	t_data;	

void	dqoute_handler(char *str, t_data *data, t_lex **lex)
{
	data->i++;
	while (str[data->i] && str[data->i] != '\"')
	{
		data->s = ft_strjoin_characters(data->s, str[data->i]);
		data->i++;
	}
	if (!str[data->i])
		printf("error in quotation\n");
	data->i++;
	if (str[data->i] == '\"')
		dqoute_handler(str, data, lex);
	else
		ft_lstadd_back_lexer(lex, new_lex(data->s, WORD));
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (TRUE);
	return (FALSE);
}

t_lex	*lexer(char *input)
{
	t_data	data;
	t_lex	*lex;

	data.i = -1;
	data.j = 0;
	lex = NULL;
	data.s = NULL;
	while (input[++data.i])
	{
		if (input[data.i] == '\"')
			dqoute_handler(input, &data, &lex);
		if (is_whitespace(input[data.i]) == TRUE)
		{
			while (input[data.i] && input[data.i] != ' ')
			{
				data.s = ft_strjoin_characters(data.s, input[data.i]);
				data.i++;
			}
			ft_lstadd_back_lexer(&lex, new_lex(data.s, WORD));
		}
		printf("the index   [%d] and the character [%c]\n", data.i, data.s[data.i]);
	}
	return (lex);
}

void	commence(void)
{
	t_lex	*lex;
	char	*input;

	while (1)
	{
		input = readline("minimlawi$>:");
		if (ft_strlen(input) > 0)
			input[ft_strlen(input)] = '\0';
		add_history(input);
		lex = lexer(input);
		while (lex)
		{
			if (lex->type == WORD)
				printf("|word| the token is |%s|\n", lex->str);
			lex = lex->next;
		}
	}
}

void	sigint_handler(int sig)
{
	(void)sig;
	commence();
}

int	main(void)
{
	// signal(SIGINT, sigint_handler);
	commence();
}
