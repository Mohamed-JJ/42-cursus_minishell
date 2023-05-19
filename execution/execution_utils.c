/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:32:05 by imaaitat          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/19 21:02:07 by imaaitat         ###   ########.fr       */
=======
/*   Updated: 2023/05/18 20:45:27 by mjarboua         ###   ########.fr       */
>>>>>>> a0f23b160a558bd3f2551ca6f5ed61a07e0de8b3
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void create_pip(int fd[2]) {
  if (pipe(fd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  dup2(fd[1], 1);
  close(fd[1]);
}

void read_pipe(t_cmd *p_cmd, int fd1[2]) {
  if (p_cmd->fd_in != 0 && p_cmd->infile == NULL &&
      p_cmd->heredoc_del == NULL) {
    dup2(fd1[0], 0);
    close(fd1[0]);
  }
}
void execution1(t_env *headd, t_cmd *p_cmd, char **env) {
  int fd2[2];
  int fd1[2];
  int fd_in;
  int fd_out;
  int fd_heredoc;
  int out = dup(1);
  int in = dup(0);
  while (p_cmd) {
    dup2(out, 1);
    dup2(in, 0);
<<<<<<< HEAD

    if (p_cmd->next && p_cmd->outfile == NULL && p_cmd->heredoc_del == NULL) {
      if (p_cmd->fd_in == 2) {
        create_pip(fd1);
        p_cmd->next->fd_in = 1;
      } else {
        create_pip(fd2);
        p_cmd->next->fd_in = 2;
      }
=======
    if (p_cmd->outfile) {
      fd_out = create_out_files(p_cmd);
      dup2(fd_out, 1);
     close(fd_out);
    }
    else if(p_cmd->next)
    {
      pipe(fd);
      dup2(fd[1], 1);
      close(fd[1]);
      p_cmd->next->fd_in = 1;
>>>>>>> a0f23b160a558bd3f2551ca6f5ed61a07e0de8b3
    }
    int pid = fork();
    if (pid == 0) {
    
    if (p_cmd->heredoc_del)
      fd_heredoc = check_heredoc(p_cmd->heredoc_del);
    if (p_cmd->infile)
      fd_in = create_in_files(p_cmd);
    if (p_cmd->outfile)
       create_out_files(p_cmd);
    if (p_cmd->h_i == 1) {
      dup2(fd_heredoc, 0);
      close(fd_heredoc);
    } else if (p_cmd->h_i == 0 && p_cmd->infile != NULL)
    {
      dup2(fd_in, 0);
      close(fd_in);
    }
      if (p_cmd->fd_in == 1)
        read_pipe(p_cmd, fd1);
      else if (p_cmd->fd_in == 2)
        read_pipe(p_cmd, fd2);
      if (builtin_cmd(p_cmd->command, p_cmd->args, &headd))
        exit(0);
      else
        execution(p_cmd->command, p_cmd->args);
    }
    waitpid(-1, &status, 0);
    status = WEXITSTATUS(status);
    p_cmd = p_cmd->next;
  }
<<<<<<< HEAD
=======
  free_env(headd);
>>>>>>> a0f23b160a558bd3f2551ca6f5ed61a07e0de8b3
}