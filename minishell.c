/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/09 00:53:30 by mjarboua         ###   ########.fr       */
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

void	qoute_handler(char *str, t_data *data, t_lex **lex)
{
	data->i++;
	printf("the string   %s\n", data->s);
	printf("the string   %s\n", str);
	while (str[data->i] && str[data->i] != data->c)
	{
		data->s = ft_strjoin_characters(data->s, str[data->i]);
		printf("the string   %s\n", data->s);
		data->i++;
	}
	if (!str[data->i])
		printf("error in quotation\n");
	data->i++;
	if (str[data->i] == '\"')
		qoute_handler(str, data, lex);
	else
		ft_lstadd_back_lexer(lex, new_lex(data->s, WORD));
}

t_lex	*lexer(char *input)
{
	t_lex	*lex;
	t_data	data;

	data.i = 0;
	lex = NULL;
	data.s = NULL;
	while (input[data.i])
	{
		if (input[data.i] == '\"' || input[data.i] == '\'')
		{
			data.c = input[data.i];
			qoute_handler(input, &data, &lex);
			free(data.s);
			data.s = NULL;
		}		else
		{
			// while (input[data.i] == ' ' && input[data.i])
			// 	data.i++;
			while (input[data.i] != ' ' && input[data.i])
			{
				data.s = ft_strjoin_characters(data.s, input[data.i]);
				data.i++;
			}
			ft_lstadd_back_lexer(&lex, new_lex(data.s, WORD));
			free(data.s);
			data.s = NULL;
		}
		data.i++;
	}
	return (free(input), lex);
}

int	skip_special_characters(char *str, int *i, char c)
{
	while (str[*i] && str[*i] == c)
		(*i)++;
	return (2);
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
		skip_special_characters(input, &i, ' ');
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

int	main(int c, char **v, char **env)
{
	t_lex	*lex;
	char	*input;

	(void)c;
	(void)v;
	(void)env;
	while (1)
	{
		input = readline("minimlawi$>:");
		if (ft_strlen(input) > 0)
			input[ft_strlen(input)] = '\0';
		add_history(input);
		input = insert_spaces(input);
		printf("intput is %s\n", input);
		lex = lexer(input);
		while (lex)
		{
			printf("|   %s  | and its type is word\n", lex->str);
			lex = lex->next;
		}
	}
}
