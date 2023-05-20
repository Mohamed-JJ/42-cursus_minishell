/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 21:43:22 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/19 20:57:18 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

static int	check_operator(t_lex *s)
{
	if (s->next == NULL)
		return (printf("minishell : syntax error\n"), 1);
	else if (s->next && ((s->type == APPEND && s->next->type == APPEND)
			|| (s->type == REDIRECT && s->next->type == REDIRECT)))
		return (printf("minishell : syntax error\n"), 1);
	else if (s->next && s->next->type != OUT_FILE
		&& (s->type == REDIRECT || s->type == APPEND))
		return (printf("minishell : syntax error\n"), 1);
	else if (s->next && s->type == HEREDOC && s->next->type != HEREDOC_DEL)
		return (printf("minishell : syntax error\n"), 1);
	else if (s->next && s->type == READ_INPUT && s->next->type != IN_FILE)
		return (printf("minishell : syntax error\n"), 1);
	else if (s->next && (s->type == PIPE && s->next->type == PIPE))
		return (printf("minishell : syntax error\n"), 1);
	return (0);
}

int	generate_error(t_lex *s)
{
	int		x;
	t_lex	*tmp;

	tmp = s;
	while (tmp)
	{
		x = 0;
		if (tmp->str[0] == '|' || tmp->str[0] == '<' || tmp->str[0] == '>')
			while (tmp->str[x])
				x++;
		if (!tmp->ds_quote && ((tmp->str[0] == '|' && x > 1)
				|| (tmp->str[0] == '<' && x > 2)
				|| (tmp->str[0] == '>' && x > 2)))
			return (printf("minishell : syntax error\n"), 1);
		if (tmp->type == APPEND || tmp->type == REDIRECT
			|| tmp->type == PIPE || tmp->type == READ_INPUT)
		{
			if (check_operator(tmp))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	redirection_type(int type, int *d)
{
	if (type == REDIRECT)
		*d = TO_BE_REDIRECTED;
	else if (type == APPEND)
		*d = TO_BE_APPENDED;
}

char	**create_arrays_of_files(t_lex *s)
{
	char	**ret;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	ret = malloc(sizeof(char *) * 5);
	while (i < 4)
	{
		ret[i] = NULL;
		i++;
	}
	while (s && s->type != PIPE)
	{
		fill_array(ret, s->type, s->str);
		s = s->next;
	}
	ret[4] = NULL;
	return (ret);
}

void	check_arr(char **r)
{
	if (!r[0])
		r[0] = ft_strdup_parsing("");
	if (!r[1])
		r[1] = ft_strdup_parsing("");
	if (!r[2])
		r[2] = ft_strdup_parsing("");
	if (!r[3])
		r[3] = ft_strdup_parsing("");
}

