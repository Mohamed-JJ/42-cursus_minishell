/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:52:39 by imaaitat          #+#    #+#             */
/*   Updated: 2023/05/26 15:30:36 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char *command, char **env, t_env *tmp)
{
	char	*path;
	char	**dir;
	int		i;

	i = -1;
	if (ft_strchr(command, '/'))
		path = command;
	else
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, "PATH") ||!ft_strcmp(tmp->name, "rix"))
				break ;
			tmp = tmp->next;
		}
		dir = ft_split(tmp->value, ':');
		while (dir[++i])
		{
			path = ft_strjoin(dir[i], "/");
			path = ft_strjoin(path, command);
			if (access(path, X_OK) == 0)
				break ;
		}
	}
	return (path);
}

void	execution(char *command, char **args, t_env **head, char **env)
{
	char	*path;
	char	**args1;
	t_env	*tmp;
	int		i;

	i = 0;
	path = get_path(command, env, (tmp = *head));
	if (args != NULL)
		args1 = cp_arr(args, command);
	else
	{
		args1 = malloc(sizeof(char *) * 2);
		args1[0] = ft_strdup(path);
		args1[1] = NULL;
	}
	if (command == NULL || !ft_strlen(command))
		exit(0);
	if (execve(path, args1, env) == -1)
	{
		printf("minishell: command not found: %s\n", command);
		exit(127);
	}
	free_array(args1);
}

int	builtin_cmd3(char *command, char **args, t_env **head)
{
	t_env	*tmp;

	if (ft_strcmp(command, "export") == 0)
	{
		if (args == NULL)
		{
			tmp = copy_env(*head);
			sort_env(&tmp);
			print_env(&tmp, 1);
			free_env(tmp);
			return (1);
		}
		else
		{
			set_env(args, *head);
			return (1);
		}
		return (1);
	}
	return (0);
}

int	builtin_cmd2(char *command, char **args, t_env **head)
{
	if (ft_strcmp(command, "env") == 0)
		return (print_env(head, 0), 1);
	if (ft_strcmp(command, "unset") == 0)
		return (unset_env(args, head), 1);
	if (ft_strcmp(command, "exit") == 0)
		return (ft_exit(args), 1);
	if (builtin_cmd3(command, args, head))
		return (1);
	if (ft_strcmp(command, "cd") == 0)
	{
		if (args != NULL)
			ft_cd(args[0], head);
		else
			ft_cd("/Users/imaaitat", head);
		return (1);
	}
	return (0);
}

int	builtin_cmd(char *command, char **args, t_env **head)
{
	if (ft_strcmp(command, "pwd") == 0)
	{
		ft_pwd(1);
		return (1);
	}
	if (ft_strcmp(command, "echo") == 0)
	{
		ft_echo(args);
		return (1);
	}
	if (ft_strcmp(command, "exit") == 0)
	{
		exit(1);
		return (1);
	}
	return (0);
}
