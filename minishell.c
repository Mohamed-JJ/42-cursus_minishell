/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/07 00:35:43 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct l_var
{
	int		i;
	int		j;
	int		x;
}		t_var;

void	fill_with_space(char *string, t_var *f, char **ret, char c)
{
	(*ret)[f->j++] = ' ';
	while (string[f->i] == c)
		(*ret)[f->j++] = string[f->i++];
	(*ret)[f->j++] = ' ';
	(*ret)[f->j] = string[f->i];
}

char	*string_with_spaces(char *string, int i, int counter)
{
	t_var	var;
	char	*ret;

	var.i = 0;
	var.j = 0;
	printf("counter: %d\n", i);
	ret = malloc(i + counter + 1);
	while (string[var.i])
	{
		if (string[var.i] == '|' || string[var.i] == '>'
			|| string[var.i] == '<')
			fill_with_space(string, &var, &ret, string[var.i]);
		else
			ret[var.j] = string[var.i];
		var.j++;
		var.i++;
	}
	ret[var.j] = '\0';
	printf("hna\n");
	return (ret);
}

int	skip_special_characters(char *str, int *i, char c)
{
	while (str[*i] && str[*i] == c)
		(*i)++;
	return (2);
}

char	*expanded_string(char *str)
{
	int		i;
	int		counter;
	char	*ret;

	i = 0;
	counter = 0;
	while (str[i])
	{
		printf("wasup\n");
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			counter += skip_special_characters(str, &i, str[i]);
		if (!str[i])
			break ;
		i++;
	}
	ret = string_with_spaces(str, i, counter);
	// free(str);
	// str = NULL;
	return (ret);
}



t_lex	*lexer(char *input)
{
	char	*holder;
	t_lex	*lex;
	int		i;
	int		beginning;

	i = 0;
	beginning = 0;
	lex = NULL;
	while (input[i])
	{
		if (!beginning)
		{
			while (input[i] != ' ' && input[i])
			{
				holder = ft_strjoin_characters(holder, input[i]);
				i++;
			}
			ft_lstadd_back_lexer(&lex, new_lex(&holder, COMMAND));
			beginning = 1;
		}
		else
		{
			while (input[i] && input[i] != ' ')
			{
				holder = ft_strjoin_characters(holder, input[i]);
				i++;
			}
			if (check_if_operator(holder))
			{
				if (!ft_strcmp(holder, "|"))
					ft_lstadd_back_lexer(&lex, new_lex(&holder, PIPE));
				else if (!ft_strcmp(holder, ">"))
					ft_lstadd_back_lexer(&lex, new_lex(&holder, REDIRECT));
				else if (!ft_strcmp(holder, "<"))
					ft_lstadd_back_lexer(&lex, new_lex(&holder, READ_INPUT));
				else if (!ft_strcmp(holder, ">>"))
					ft_lstadd_back_lexer(&lex, new_lex(&holder, APPEND));
				else if (!ft_strcmp(holder, "<<"))
					ft_lstadd_back_lexer(&lex, new_lex(&holder, HEREDOC));
				beginning = 0;
			}
			else
				ft_lstadd_back_lexer(&lex, new_lex(&holder, ARGUMENT));
		}
		i++;
	}
	return (lex);
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
		// input = expanded_string(input);
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

// you consider making your delimiter a redirection
// of any type and pipe operators or the and operator

// first we should work on orgainzing our commands and their arguments and manage the redirections and pipes
// as soon as we find a redirection or a pipe we should split the string into part according to how many redirections and pipes we have