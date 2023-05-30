/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_7.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:52:39 by imaaitat          #+#    #+#             */
/*   Updated: 2023/05/29 23:26:44 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdint.h>

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*get_value_env(char *name, t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_exit(char **args)
{
	if (args != NULL)
	{
		if (arr_len(args) > 1)
		{
			printf("exit\n");
			printf("minishell: exit: too many arguments\n");
			g_status = 1;
		}
		else if (check_digit(args[0]) || ft_atoi(args[0]) < -2147483647)
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", args[0]);
			exit(255);
		}
		else
		{
			printf("exit\n");
			exit(ft_atoi(args[0]));
		}
	}
	else
	{
		printf("exit\n");
		exit(g_status);
	}
}

void	set_delete(char *name, char *value, t_env **head)
{
	char	*value2;
	char	*eqoul;

	if (name == NULL)
		return ;
	if (value == NULL)
		value = ft_strdup(get_value_env("PWD", head));
	if (value[0] != '=')
		eqoul = ft_strdup("=");
	else
		eqoul = ft_strdup("");
	value2 = ft_strjoin(eqoul, value);
	delete_env(head, name);
	ft_lstback(head, ft_strdup(name), value2);
	if (value)
		free(value);
}

void	free2(char *name, char *value)
{
	free(name);
	free(value);
}
