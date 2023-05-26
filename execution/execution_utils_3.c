/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:10:32 by imaaitat          #+#    #+#             */
/*   Updated: 2023/05/26 13:06:32 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var(char *var)
{
	int		i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*get_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	name = (char *)malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	while (str[i + j])
		j++;
	value = (char *)malloc(sizeof(char) * (j + 1));
	if (!value)
		return (NULL);
	j = 0;
	while (str[i])
	{
		value[j] = str[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

t_env	*set_env(char **env, t_env *head)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (env[i])
	{
		if (chek_plus(env[i]) && check_var(env[i]))
		{
			name = get_name(env[i]);
			value = get_value(env[i]);
			serch_replace(head, name, value);
			free(name);
			free(value);
		}
		else if (ft_strchr(env[i], '=')
			&& !ft_strchr(env[i], '+') && check_var(env[i]))
			ft_lstback(&head, get_name(env[i]), get_value(env[i]));
		else if (!ft_strchr(env[i], '+') && check_var(env[i]))
			ft_lstback(&head, get_name(env[i]), get_value(env[i]));
		else
			printf("invslid identifier\n");
		i++;
	}
	return (head);
}

t_env	*copy_env(t_env *head)
{
	t_env	*head2;
	t_env	*tmp;

	head2 = NULL;
	tmp = head;
	while (tmp)
	{
		ft_lstback(&head2, get_name(tmp->name), get_value(tmp->value));
		tmp = tmp->next;
	}
	return (head2);
}
