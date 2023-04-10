/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/10 14:01:21 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct l_data
{
	int		i;
	char	c;
	char	*s;
}		t_data;

char	*token_(char *str, int *iter)
{
	int		i;
	char	*ret;

	i = *iter;
	ret = NULL;
	while (str[i] != ' ' && str[i])
	{
		ret = ft_strjoin_characters(ret, str[i]);
		i++;
	}
	*iter = i;
	return (ret);
}

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

char	*insert_spaces(char *input)
{
	int		i;
	char	*ret;
	char	character;

	i = -1;
	ret = NULL;
	while (input[++i])
	{
		// skip_special_characters(input, &i, ' ');
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
	printf("the string after the insertion %s\n", ret);
	return (ret);
}

int	main(void)
{
	t_lex	*lex;
	char	*input;

	while (1)
	{
		input = readline("minimlawi$>:");
		if (ft_strlen(input) > 0)
			input[ft_strlen(input)] = '\0';
		add_history(input);
		input = insert_spaces(input);
		lex = lexer(input);
		while (lex)
		{
			printf("%s and it's type is word\n", lex->str);
			lex = lex->next;
		}
	}
}
