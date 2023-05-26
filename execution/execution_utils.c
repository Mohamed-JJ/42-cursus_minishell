/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:32:05 by imaaitat          #+#    #+#             */
/*   Updated: 2023/05/25 22:37:40 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct exe_fd
{
	int	fd2[2];
	int	fd1[2];
	int	fd_in;
	int	fd_out;
	int	outfile;
	int	fd_heredoc;
	int	out;
	int	in;
	int	pid;
}		t_exe_fd;

void	create_pip(int fd[2], t_cmd *p_cmd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	dup2(fd[1], 1);
	close(fd[1]);
	if (p_cmd->outfile != NULL || p_cmd->heredoc_del != NULL)
		write(fd[1], " ", 1);
}

void	read_pipe(t_cmd *p_cmd, int fd1[2])
{
	if (p_cmd->fd_in != 0 && p_cmd->infile == NULL
		&& p_cmd->heredoc_del == NULL)
	{
		dup2(fd1[0], 0);
		close(fd1[0]);
	}
}

int	exec_write(t_exe_fd *exe_fd, t_cmd *p_cmd)
{
	dup2(exe_fd->out, 1);
	dup2(exe_fd->in, 0);
	if (p_cmd->heredoc_del && exe_fd->fd_heredoc != -1)
		exe_fd->fd_heredoc = check_heredoc(p_cmd->heredoc_del);
	if (exe_fd->fd_heredoc == -1)
		return (1);
	if (p_cmd->infile)
		exe_fd->fd_in = create_in_files(p_cmd);
	if (p_cmd->outfile)
		exe_fd->outfile = create_out_files(p_cmd);
	if (p_cmd->next)
	{
		if (p_cmd->fd_in == 2)
		{
			create_pip(exe_fd->fd1, p_cmd);
			p_cmd->next->fd_in = 1;
		}
		else
		{
			create_pip(exe_fd->fd2, p_cmd);
			p_cmd->next->fd_in = 2;
		}
	}
	return (0);
}

void	exec_read(t_exe_fd *exe_fd, t_cmd *p_cmd)
{
	if (p_cmd->h_i == 1)
	{
		dup2(exe_fd->fd_heredoc, 0);
		close(exe_fd->fd_heredoc);
	}
	else if (p_cmd->h_i == 0)
	{
		dup2(exe_fd->fd_in, 0);
		close(exe_fd->fd_in);
	}
	if (p_cmd->outfile)
	{
		dup2(exe_fd->outfile, 1);
		close(exe_fd->outfile);
	}
	if (p_cmd->fd_in == 1)
		read_pipe(p_cmd, exe_fd->fd1);
	else if (p_cmd->fd_in == 2)
		read_pipe(p_cmd, exe_fd->fd2);
	else if (p_cmd->infile == NULL && p_cmd->heredoc_del == NULL && p_cmd->next)
	{
		p_cmd->fd_in = open("/dev/null", O_RDONLY);
		dup2(p_cmd->fd_in, 0);
		close(p_cmd->fd_in);
	}
}

void	execution1(t_env **headd, t_cmd *p_cmd, char **env)
{
	t_exe_fd	exe_fd;

	exe_fd.out = dup(1);
	exe_fd.in = dup(0);
	while (p_cmd)
	{
		if (!exec_write(&exe_fd, p_cmd) && builtin_cmd2(p_cmd->command,
				p_cmd->args, headd))
			g_status = 0;
		else if (exe_fd.fd_heredoc != -1)
		{
			exe_fd.pid = fork();
			if (exe_fd.pid == 0 && exe_fd.fd_heredoc != -1)
			{
				exec_read(&exe_fd, p_cmd);
				if (builtin_cmd(p_cmd->command, p_cmd->args, headd))
					exit(0);
				else
					execution(p_cmd->command, p_cmd->args, headd, env);
			}
		}
		waitpid(-1, &g_status, 0);
		g_status = WEXITSTATUS(g_status);
		p_cmd = p_cmd->next;
	}
}
