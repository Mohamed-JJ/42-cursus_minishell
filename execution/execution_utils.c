/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:32:05 by imaaitat          #+#    #+#             */
/*   Updated: 2023/05/17 21:31:37 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execution1(t_env *headd,t_cmd *p_cmd, char **env)
{
	int fd[2];
	int fd_in;
	int fd_heredoc;
	int out = dup(1);
	int in = dup(0);
	t_env *head;

	head = NULL;
	headd = set_env(env, head);
	while (p_cmd != NULL)
	{
		dup2(out, 1);
		dup2(in, 0);
		if (p_cmd->heredoc_del)
			fd_heredoc = check_heredoc(p_cmd->heredoc_del);
		if (p_cmd->infile)
			fd_in = create_in_files(p_cmd);
		if (p_cmd->outfile)
			create_out_files(p_cmd);
		if (p_cmd->next != NULL && p_cmd->outfile == NULL)
		{
			pipe(fd);
			dup2(fd[1], 1);
			close(fd[1]);
			p_cmd->next->fd_in = 1;
		}
		if(p_cmd->h_i == 1)
		{
			dup2(fd_heredoc, 0);
			close(fd_heredoc);
		}
		else if (p_cmd->fd_in == 0)
		{
			dup2(fd_in, 0);
			close(fd_in);
		}
    	int pid = fork();
    	if (pid == 0) {
    		if (p_cmd->fd_in != 0 && p_cmd->infile == NULL)
			{
    	    	dup2(fd[0], 0);
    	    	close(fd[0]);
			}
    		if (builtin_cmd(p_cmd->command, p_cmd->args, headd))
    	    	exit(0);
    		else
    	    	execution(p_cmd->command, p_cmd->args);
    	}
    	waitpid(-1, &status, 0);
    	status = WEXITSTATUS(status);
    	p_cmd = p_cmd->next;
	}
	free_env(headd);
}
