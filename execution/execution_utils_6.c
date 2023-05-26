/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:52:39 by imaaitat          #+#    #+#             */
/*   Updated: 2023/05/26 15:22:20 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_shell_level(char **env)
{
	char	*name;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (env[++i])
	{
		name = get_name(env[i]);
		if (ft_strcmp("SHLVL", name) == 0)
		{
			while (env[i][j])
			{
				if (env[i][j] == '=')
				{
					env[i][j + 1] += 1;
					free(name);
					return ;
				}
				j++;
			}
		}
		free(name);
	}
	return ;
}

t_env	*sort_env(t_env **head)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*tmp_name;
	char	*tmp_value;

	tmp2 = *head;
	while (tmp2)
	{
		tmp = *head;
		while (tmp)
		{
			if (ft_strcmp(tmp->name, tmp2->name) > 0)
			{
				tmp_name = tmp->name;
				tmp_value = tmp->value;
				tmp->name = tmp2->name;
				tmp->value = tmp2->value;
				tmp2->name = tmp_name;
				tmp2->value = tmp_value;
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (*head);
}

void	print_env(t_env **env, int i)
{
	t_env	*tmp;

	tmp = *env;
	if (!env)
		return ;
	while (tmp)
	{
		if (i && ft_strcmp(tmp->name, "_")
			== 0 || ft_strcmp(tmp->name, "rix") == 0)
		{
			tmp = tmp->next;
			continue ;
		}
		if (i == 1 && ft_strcmp(tmp->name, "rix") != 0)
		{
			if (ft_strcmp(tmp->value, "") != 0)
				printf("declare -x %s%.1s\"%s\"\n", tmp->name, tmp->value,
					tmp->value + 1);
			else
				printf("declare -x %s\n", tmp->name);
		}
		else if (tmp != NULL && ft_strcmp(tmp->value, "") != 0)
			printf("%s%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = (env)->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	free(env);
}

void	ft_cd(char *argv, t_env **head)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (ft_strcmp(argv, "-") == 0)
	{
		if (chdir(get_value_env("OLDPWD=", head)) != 0)
		{
			printf("minishell: cd: OLDPWD not set\n");
			g_status = 1;
		}
		else
			printf("%s\n", get_value_env("OLDPWD=", head));
	}
	else if (chdir(argv) != 0)
	{
		perror("cd");
		g_status = 1;
	}
	else
		g_status = 0;
	delete_env(head, "OLDPWD=");
	ft_lstback(head, ft_strdup("OLDPWD="), pwd);
	return ;
}
