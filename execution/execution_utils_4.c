/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:33:05 by imaaitat          #+#    #+#             */
/*   Updated: 2023/05/29 17:25:25 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_env(char **args, t_env **head)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = *head;
	if (args == NULL)
		return ;
	while (args[i])
	{
		if (ft_strcmp(args[0], "?") == 0 || ft_strcmp(args[0], "rix") == 0)
		{
			i++;
			continue ;
		}
		if (ft_strcmp(tmp->name, args[0]) == 0)
		{
			*head = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return ;
		}
		delete_env(head, args[i]);
		i++;
	}
}

void	delete_env(t_env **head, char *name)
{
	t_env	*current;
	t_env	*prev;

	if (*head == NULL)
		return ;
	if (ft_strcmp((*head)->name, name) == 0)
	{
		current = *head;
		*head = (*head)->next;
		free(current->name);
		return (free(current->value), free(current));
	}
	current = *head;
	prev = NULL;
	while (current != NULL && ft_strcmp(current->name, name) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	prev->next = current->next;
	free(current->name);
	free(current->value);
	free(current);
}

int	serch_replace(t_env *head, char *name, char *value)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			value++;
			if (ft_strcmp(tmp->value, "") != 0)
				tmp->value = ft_strjoin(tmp->value, value);
			else if (!ft_strcmp(tmp->value, "") && !ft_strcmp(value - 1, ""))
				tmp->value = ft_strjoin(tmp->value, "");
			else
			{
				tmp->value = ft_strjoin(tmp->value, "=");
				tmp->value = ft_strjoin(tmp->value, value);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_echo(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return (g_status = 0, printf("\n"), 1);
	while (argv[i] && is_all_new_line(argv[i]) == 1)
		i++;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (is_all_new_line(argv[0]) != 1)
		ft_putstr_fd("\n", 1);
	g_status = 0;
	return (1);
}

void	handle_sig(int sig)
{
	int	i;

	i = 0;
	if (access("/tmp/h_c", X_OK) == 0 && sig == SIGINT)
	{
		unlink("/tmp/h_c");
		close(0);
		g_status = 1;
		i = 1;
	}
	if (sig == SIGINT)
	{
		if (i == 0)
			printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_status = 131;
	}
}
