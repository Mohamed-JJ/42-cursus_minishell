/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:52:39 by imaaitat          #+#    #+#             */
/*   Updated: 2023/05/28 18:11:46 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_shell_level(char **env, int f)
{
	char	*name;
	char	*value;
	char	*tmp;
	int		i;

	i = -1;
	while (env[++i])
	{
		name = get_name(env[i]);
		value = get_value(env[i]);
		if (ft_strcmp("SHLVL", name) == 0)
		{
			tmp = ft_itoa(ft_atoi(value + 1) + 1);
			if (f == 1)
				free(env[i]);
			env[i] = ft_strjoin(ft_strdup("SHLVL="), tmp);
			free(tmp);
		}
		free(name);
		free(value);
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
	while (tmp)
	{
		if (i && ft_strcmp(tmp->name, "_") == 0 || ft_strcmp(tmp->name,
				"rix") == 0 || ft_strcmp(tmp->name, "?") == 0)
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
		else if (tmp->value != NULL && ft_strcmp(tmp->value, "=")
			&& ft_strcmp(tmp->value, ""))
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
	if (argv && ft_strcmp(argv, "-") == 0)
	{
		if (chdir(get_value_env("OLDPWD", head) + 1) != 0)
		{
			printf("minishell: cd: OLDPWD not set\n");
			g_status = 1;
		}
		else if (get_value_env("OLDPWD", head) != NULL)
			printf("%s\n", get_value_env("OLDPWD", head) + 1);
	}
	else if (argv && ft_strcmp(argv, ".") == 0 && !getcwd(NULL, 0))
		perror("cd");
	else if (argv && chdir(argv) != 0)
	{
		perror("cd");
		g_status = 1;
	}
	else
		g_status = 0;
	set_delete("OLDPWD", pwd, head);
	set_delete("PWD", getcwd(NULL, 0), head);
}
