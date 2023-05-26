/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:52:39 by imaaitat          #+#    #+#             */
/*   Updated: 2023/05/26 13:08:28 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <signal.h>

//--------------------------------------herdoc-----
void	all_heredoc(char **del, int count, char *input, int fd)
{
	int		i;

	i = 0;
	while (input != NULL && i < count - 1)
	{
		if (input != NULL && ft_strcmp(input, del[i]) == 0)
			i++;
		free(input);
		input = readline("heredoc>");
	}
	while (input != NULL && ft_strcmp(input, del[count - 1]) != 0)
	{
		ft_putendl_fd(input, fd);
		free(input);
		input = readline("heredoc>");
	}
	free(input);
}

int	check_heredoc(char **del)
{
	int		count;
	char	*input;
	int		fd;
	int		i;

	i = 0;
	fd = open("/tmp/heredoc", O_RDWR | O_CREAT, 0777);
	input = readline("heredoc>");
	count = arr_len(del);
	if (count == 1)
	{
		while (input != NULL && ft_strcmp(input, del[count - 1]) != 0)
		{
			ft_putendl_fd(input, fd);
			free(input);
			input = readline("heredoc>");
		}
		free(input);
	}
	else
		all_heredoc(del, count, input, fd);
	close(fd);
	fd = open("/tmp/heredoc", O_RDONLY);
	return (unlink("/tmp/heredoc"), fd);
}

int	create_in_files(t_cmd *p_cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (p_cmd->infile[i])
	{
		if (access(p_cmd->infile[i], F_OK) == 0)
		{
			fd = open(p_cmd->infile[i], O_RDWR);
			if (fd == -1)
				return (0);
		}
		else
			printf("%s No such file or directory\n", p_cmd->infile[i]);
		if (p_cmd->infile[i + 1] != NULL)
			close(fd);
		i++;
	}
	return (fd);
}

int	create_out_files(t_cmd *p_cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (p_cmd->outfile[i])
	{
		if (p_cmd->is_red_or_app == 2)
			fd = open(p_cmd->outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0777);
		else
			fd = open(p_cmd->outfile[i], O_RDWR | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
		{
			perror("open");
			return (0);
		}
		if (p_cmd->outfile[i + 1] != NULL)
			close(fd);
		i++;
	}
	return (fd);
}

int	ft_pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	free(pwd);
	return (1);
}
