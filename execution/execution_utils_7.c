/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_7.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:52:39 by imaaitat          #+#    #+#             */
/*   Updated: 2023/05/26 15:07:41 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr_fd_echo(char	*s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			ft_putnbr_fd(g_status, 1);
			i += 2;
		}
		write(fd, &s[i], 1);
		i++;
	}
}

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
		else if (check_digit(args[0]))
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
		exit(1);
	}
}
