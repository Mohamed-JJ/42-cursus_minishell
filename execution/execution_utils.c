/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:32:05 by imaaitat          #+#    #+#             */
/*   Updated: 2023/05/18 10:45:24 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

void execution1(t_env *headd, t_cmd *p_cmd, char **env) {
  int fd[2];
  int fd_in;
  int fd_out;
  int fd_heredoc;
  int out = dup(1);
  int in = dup(0);
  char **args1;
  t_env *head;
  head = NULL;
  headd = set_env(env, head);
  while (p_cmd != NULL) {
    dup2(out, 1);
    dup2(in, 0);
    if (p_cmd->next != NULL && p_cmd->outfile == NULL) {
      pipe(fd);
      dup2(fd[1], 1);
      close(fd[1]);
      p_cmd->next->fd_in = 1;
    }
    int pid = fork();
    if (pid == 0) 
    {
      if (p_cmd->heredoc_del)
      {
        fd_heredoc = check_heredoc(p_cmd->heredoc_del);
        dup2(fd_heredoc, 0);
        close(fd_heredoc);
      }
      if (p_cmd->infile) {
        fd_in = create_in_files(p_cmd);
        dup2(fd_in, 0);
        close(fd_in);
      }

      if (p_cmd->outfile) {
        fd_out = create_out_files(p_cmd);
        dup2(fd_out, 1);
        close(fd_out);
      }
      // if (p_cmd->h_i == 1) {
      //   dup2(fd_heredoc, 0);
      //   close(fd_heredoc);
      // } else if (p_cmd->h_i == 0 && p_cmd->infile != NULL) {
      //   dup2(fd_in, 0);
      //   close(fd_in);
      // }
      if (p_cmd->args != NULL) {
        args1 = malloc(sizeof(char *) * arr_len(p_cmd->args) + 2);
        args1[0] = ft_strdup(p_cmd->command);
        cp_arr(p_cmd->args, args1);
      } else {
        args1 = malloc(sizeof(char *) * 2);
        args1[0] = ft_strdup(p_cmd->command);
        args1[1] = NULL;
      }

      if (p_cmd->fd_in != 0 && p_cmd->infile == NULL) {
        dup2(fd[0], 0);
        close(fd[0]);
      }
      if (builtin_cmd(p_cmd->command, p_cmd->args, headd))
        exit(0);
      else
        execution(p_cmd->command, args1);
    }
    free_array(args1);
    waitpid(-1, &status, 0);
    status = WEXITSTATUS(status);
    p_cmd = p_cmd->next;
  }
  free_env(headd);
}