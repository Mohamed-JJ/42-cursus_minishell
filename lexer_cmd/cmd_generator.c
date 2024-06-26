/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:47:52 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/23 16:53:07 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*new_command(char *str, char **arr, int i, int j)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (NULL);
	if (str)
		ret->command = ft_strdup_parsing(str);
	ret->args = fill_arrays(arr[0]);
	ret->outfile = fill_arrays(arr[1]);
	ret->infile = fill_arrays(arr[2]);
	ret->heredoc_del = fill_arrays(arr[3]);
	ret->is_red_or_app = i;
	ret->h_i = j;
	ret->fd_in = 0;
	ret->next = NULL;
	return (ret);
}

void	ft_lstadd_back_cmd(t_cmd **c, t_cmd *new)
{
	t_cmd	*tmp;

	if (!c)
		return ;
	if (!*c)
	{
		*c = new;
		return ;
	}
	tmp = *c;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	here_doc_in_file_priority(int *j, int type)
{
	if (type == HEREDOC)
		*j = 1;
	else if (type == IN_FILE)
		*j = 0;
}

t_cmd	*fill_till_eol_pipe(char **str, char **arr, t_lex **s)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (*s && (*s)->type != PIPE)
	{
		redirection_type((*s)->type, &i);
		here_doc_in_file_priority(&j, (*s)->type);
		if ((*s)->type == COMMAND)
			*str = ft_strjoin_parsing(*str, (*s)->str, 0);
		else if ((*s)->type == ARGUMENT)
			arr[0] = join_string((*s)->str, &arr[0]);
		else if ((*s)->type == OUT_FILE)
			arr[1] = join_string((*s)->str, &arr[1]);
		else if ((*s)->type == IN_FILE)
			arr[2] = join_string((*s)->str, &arr[2]);
		else if ((*s)->type == HEREDOC_DEL)
			arr[3] = join_string((*s)->str, &arr[3]);
		*s = (*s)->next;
	}
	return (new_command(*str, arr, i, j));
}

t_cmd	*create_cmd(t_lex *s)
{
	char	**arr;
	char	*str;
	t_cmd	*ret;

	ret = NULL;
	arr = NULL;
	while (s)
	{
		str = ft_strdup_parsing("");
		arr = empty_array();
		ft_lstadd_back_cmd(&ret, fill_till_eol_pipe(&str, arr, &s));
		if (str)
			free_string(&str);
		check_arr(arr);
		if (arr)
			free_array(arr);
		if (s == NULL)
			break ;
		s = s->next;
	}
	return (ret);
}
