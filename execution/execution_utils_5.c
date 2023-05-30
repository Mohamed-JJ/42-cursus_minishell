/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:52:39 by imaaitat          #+#    #+#             */
/*   Updated: 2023/05/29 21:12:17 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**cp_arr(char **arr, char *str)
{
	int		i;
	char	**arr1;
	char	*tmp;
	int		j;

	j = 1;
	i = 0;
	tmp = ft_strdup(str);
	while (arr[i])
	{
		tmp = ft_strjoin(tmp, "\n");
		tmp = ft_strjoin(tmp, arr[i]);
		i++;
	}
	arr1 = ft_split(tmp, '\n');
	free(tmp);
	return (arr1);
}

void	signal_handler(int signum)
{
	if (access("/tmp/h_c", X_OK) == 0 && signum == SIGINT)
	{
		unlink("/tmp/h_c");
		close(0);
		g_status = 1;
	}
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
}

int	is_all_new_line(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_lstback(t_env **head, char *key, char *value)
{
	t_env	*new;
	t_env	*current;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = key;
	new->value = value;
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
