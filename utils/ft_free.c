/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:11:27 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/20 13:07:42 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_list(t_lex	**list)
{
	if (list && *list)
	{
		while (*list)
		{
			free((*list)->str);
			free(*list);
			if ((*list)->next == NULL)
				break ;
			*list = (*list)->next;
		}
		*list = NULL;
	}
}

void	free_cmd_list(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->next)
		free_cmd_list(cmd->next);
	if (cmd->command)
	{
		free(cmd->command);
		cmd->command = NULL;
	}
	if (cmd->args)
		free_array(cmd->args);
	if (cmd->outfile)
		free_array(cmd->outfile);
	if (cmd->infile)
		free_array(cmd->infile);
	if (cmd->heredoc_del)
		free_array(cmd->heredoc_del);
	free(cmd);
	cmd = NULL;
}

void	free_string(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

// void	free_array(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		free(arr[i]);
// 		arr[i] = NULL;
// 		i++;
// 	}
// 	arr = NULL;
// }
