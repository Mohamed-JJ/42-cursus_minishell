/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:38:38 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/18 15:57:52 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op(char *str)
{
	int		i;
	char	*ops;

	i = 0;
	ops = ft_strdup("|><");
	while (str[i])
	{
		if (ft_strchr(ops, str[i]))
			return (free(ops), 1);
		i++;
	}
	return (free(ops), 0);
}

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

t_input	*lex_input(char **str)
{
	t_input	*ret;
	int		i;

	ret = NULL;
	i = 0;
	while (str[i])
	{
		if (is_op(str[i]))
			ft_lstadd_back(&ret, ft_lstnew(str[i], 1));
		else
			ft_lstadd_back(&ret, ft_lstnew(str[i], 0));
		i++;
	}
	return (ret);
}

int	check_double_quotes(char *str)
{
	int	s;
	int	d;

	d = 0;
	s = 0;
	while (*str)
	{
		if (*str == '\'')
			s++;
		else if (*str == '\"')
			d++;
		str++;
	}
	if (d % 2 == 1 || s % 2 == 1)
		return (1);
	return (0);
}

t_cmd	*fill_list(char **str, int start, int end, int pipe)
{
	t_cmd	*h;
	int		i;

	i = 1;
	h->cmd = str[0];
	while (str[i])
	{
		if (in_out_red(str[i]))
		{
			handle_red(str, &i); // we need to handle the red in/out and i need to pass an address of the iterator in order to keep everything in order
		}
	}
	return (h);
}

void	commence(char *v)
{
	t_cmd	*h;
	char	*str;
	char	**arr;

	str = expanded_string(v);
	handle_what_inside_quote(str);
	arr = ft_split(str, ' ');
	free(str);
	h = syntax_analyser(arr);
}


char	*extract_from_quote(char *str, int *iter, char quote)
{
	int		i;
	char	*ret;

	i = *iter;
	ret = NULL;
	while (str[i] && str[i] != quote)
	{
		ret = ft_strjoin_characters(ret, str[i]);
		i++;
	}
	return (ret);
}

char	*handle_qoutes(char *input, int *i)
{
	int		s;
	int		e;

	s = 0;
	e = 0;
	if (input[*i] == '\"')
	{
		s = *i + 1;
		while (input[++*i])
			if (input[*i] == '\"')
				return (ft_substr(input, s, *i - s - 1));
	}
	else if (input[*i] == '\'')
	{
		s = *i;
		while (input[++*i])
			if (input[*i] == '\'')
				return (ft_substr(input, s, *i - s + 1));
	}
	else
	{
		while (input[*i] && input[*i] != ' ')
			(*i)++;
		return (ft_substr(input, s, *i - s));
	}
	return (NULL);
}

void	handle_what_inside_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
			while (str[++i] != 39)
				do_change(&str[i], ' ');
		else if (str[i] == 34)
			while (str[++i] != 34)
				do_change(&str[i], ' ');
		i++;
	}
}

void	do_change(char *c, int character)
{
	if (*c == character)
		*c = '\t';
}

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

char	*expand_string(char *str)
{
	char	*ret;
	char	character;
	int		i;

	i = -1;
	while (str[++i])
	{
		while ((str[i] == ' ' || str[i] == '\t') && str[i])
			i++;
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			character = str[i];
			ret = ft_strjoin_characters(ret, ' ');
			while (str[i] == character && str[i])
			{
				ret = ft_strjoin_characters(ret, character);
				i++;
			}
			ret = ft_strjoin_characters(ret, ' ');
			ret = ft_strjoin_characters(ret, str[i]);
		}
		else
		{
			while (str[i] != ' ' && str[i] != '|'
				&& str[i] != '>' && str[i] != '<' && str[i])
			{
				ret = ft_strjoin_characters(ret, character);
				i++;
			}
		}
	}
	return (ret);
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

int	skip_special_characters(char *str, int *i, char c)
{
	while (str[*i] && str[*i] == c)
		(*i)++;
	return (2);
}

void	add_back_type(t_lex **lex, char *holder, int *i)
{
	if (check_if_operator(holder))
	{
		if (!ft_strcmp(holder, "|"))
		{
			ft_lstadd_back_lexer(lex, new_lex(holder, PIPE));
			*i = 0;
		}
		else if (!ft_strcmp(holder, ">"))
			ft_lstadd_back_lexer(lex, new_lex(holder, REDIRECT));
		else if (!ft_strcmp(holder, "<"))
			ft_lstadd_back_lexer(lex, new_lex(holder, READ_INPUT));
		else if (!ft_strcmp(holder, ">>"))
			ft_lstadd_back_lexer(lex, new_lex(holder, APPEND));
		else if (!ft_strcmp(holder, "<<"))
			ft_lstadd_back_lexer(lex, new_lex(holder, HEREDOC));
	}
	else
		ft_lstadd_back_lexer(lex, new_lex(holder, ARGUMENT));
		// check_add_argument(lex, holder);
}

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

// char	*expand_variables(char *input, t_exp *p)
// {
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	ret = NULL;
// 	while (input[i])
// 	{
// 		if (input[i] == '$')
// 		{
// 			i++;
// 			while (p)
// 			{
// 				if (input[i] == p->name[0])
// 				{
// 					ret = ft_strjoin_characters(ret, p->value);
// 					break ;
// 				}
// 				p = p->next;
// 			}
// 		}
// 		else
// 			ret = ft_strjoin_characters(ret, input[i]);
// 		i++;
// 	}
// }

t_exp	*store_local_var(char *input)
{
	char	**arr;
	t_exp	*p;
	t_data	h;

	h.i = 0;
	arr = malloc(sizeof(char *) * 3);
	arr[3] = NULL;
	p = NULL;
	while (input[h.i])
	{
		if (input[h.i] == '=')
		{
			while ((input[h.i] != '\t' || input[h.i] != ' ') && input[h.i])
				h.i--;
			h.i++;
			while (input[h.i] && input[h.i] != '=')
			{
				arr[0] = ft_strjoin_characters(arr[0], input[h.i]);
				h.i++;
			}
			h.i++;
			while (input[h.i] != '\t' && input[h.i] != ' ' && input[h.i])
			{
				arr[1] = ft_strjoin_characters(arr[1], input[h.i]);
				h.i++;
			}
			ft_lstadd_back_expander(&p, new_exp(arr));
			free(arr[0]);
			free(arr[1]);
			arr[0] = NULL;
			arr[1] = NULL;
		}
		// while ((input[h.i] == '\t' || input[h.i] != ' ') && input[h.i])
		// 	h.i++;
		// while (input[h.i] != '\t' && input[h.i] != ' ' && input[h.i])
			// i++;
		if (input[h.i])
			h.i++;
		else
			break ;
	}
	return (p);
}


