/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 21:43:22 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/10 21:46:40 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	generate_error(t_lex *s)
{
	int	i;

	i = 0;
	while (s)
	{
		if (generate_error2(s, &i))
			return (1);
		else if (!s->prev && !ft_strncmp(s->str, ">", 1) && s->next)
		{
			s = s->next;
			continue ;
		}
		else if (i == 0 && check_if_operator(s->str) && s->next)
		{
			s = s->next;
			continue ;
		}
		else if (!s->prev && !ft_strncmp(s->str, "<", 1) && s->next)
		{
			s = s->next;
			continue ;
		}
		s = s->next;
	}
	return (0);
}

void	redirection_type(int type, t_data *d)
{
	if (type == REDIRECT)
		d->i = TO_BE_REDIRECTED;
	else if (type == APPEND)
		d->i = TO_BE_APPENDED;
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
		r[0] = ft_strdup("");
	if (!r[1])
		r[1] = ft_strdup("");
	if (!r[2])
		r[2] = ft_strdup("");
	if (!r[3])
		r[3] = ft_strdup("");
}

int	generate_error2(t_lex *s, int *i)
{
	if (s->type == COMMAND)
		*i = 1;
	else if (s->prev && s->type == PIPE && s->next)
		*i = 0;
	if (s->next && check_if_operator(s->str) && check_if_operator(s->next->str))
		return (printf("minishell : syntax error\n"), 1);
	else if (!s->prev && !ft_strncmp(s->str, "<", 1) && !s->next)
		return (printf("minishell : syntax error\n"), 1);
	else if (!s->prev && !ft_strncmp(s->str, ">", 1) && !s->next)
		return (printf("minishell : syntax error\n"), 1);
	else if (!s->next && check_if_operator(s->str))
		return (printf("minishell : syntax error\n"), 1);
	return (0);
}
