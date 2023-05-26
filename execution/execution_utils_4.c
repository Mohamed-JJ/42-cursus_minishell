/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:33:05 by imaaitat          #+#    #+#             */
/*   Updated: 2023/05/26 15:14:14 by imaaitat         ###   ########.fr       */
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
	{
		return ;
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

int	chek_plus(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '+' && str[j + 1] == '=' && ft_isalpha(str[j - 1]))
			return (1);
		j++;
	}
	return (0);
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
	while (argv[i])
	{
		if (is_all_new_line(argv[0]) == 1)
			i++;
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (is_all_new_line(argv[0]) != 1)
		ft_putstr_fd("\n", 1);
	return (1);
}
