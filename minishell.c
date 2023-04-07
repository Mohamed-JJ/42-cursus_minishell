/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/07 20:30:05 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct l_var
{
	int		i;
	int		j;
	int		x;
	char	*str;
}		t_var;

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

void	add_back_type(t_lex **lex, char *holder, int *i)
{
	if (check_if_operator(holder))
	{
		if (!ft_strcmp(holder, "|"))
			ft_lstadd_back_lexer(lex, new_lex(holder, PIPE));
		else if (!ft_strcmp(holder, ">"))
			ft_lstadd_back_lexer(lex, new_lex(holder, REDIRECT));
		else if (!ft_strcmp(holder, "<"))
			ft_lstadd_back_lexer(lex, new_lex(holder, READ_INPUT));
		else if (!ft_strcmp(holder, ">>"))
			ft_lstadd_back_lexer(lex, new_lex(holder, APPEND));
		else if (!ft_strcmp(holder, "<<"))
			ft_lstadd_back_lexer(lex, new_lex(holder, HEREDOC));
		*i = 0;
	}
	else
		ft_lstadd_back_lexer(lex, new_lex(holder, ARGUMENT));
}

t_lex	*lexer(char *input)
{
	char	*holder;
	t_lex	*lex;
	int		i;
	int		beginning;

	i = -1;
	beginning = 0;
	lex = NULL;
	while (input[++i])
	{
		if (!beginning)
		{
			holder = token_(input, &i);
			ft_lstadd_back_lexer(&lex, new_lex(holder, COMMAND));
			beginning = 1;
		}
		else
		{
			holder = token_(input, &i);
			add_back_type(&lex, holder, &beginning);
		}
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
				ret = ft_strjoin_characters(ret, input[i++]);
				if (input[i + 1] != character)
					break ;
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
		lex = lexer(input);
		while (lex)
		{
			if (lex->type == COMMAND)
				printf("%s and its type is command\n", lex->str);
			else if (lex->type == ARGUMENT)
				printf("%s and it's type is argument\n", lex->str);
			else if (lex->type == PIPE)
				printf("%s and it's type is pipe\n", lex->str);
			else if (lex->type == REDIRECT)
				printf("%s and it's type is redirect\n", lex->str);
			else if (lex->type == READ_INPUT)
				printf("%s and it's type is read input\n", lex->str);
			else if (lex->type == APPEND)
				printf("%s and it's type is append\n", lex->str);
			else if (lex->type == HEREDOC)
				printf("%s and it's type is heredoc\n", lex->str);
			lex = lex->next;
		}
	}
}
