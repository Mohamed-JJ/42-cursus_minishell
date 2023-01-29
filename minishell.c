/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/01/29 20:37:27 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int c, char **v, char **env)
{
	// char	*s[] = {"/bin/ls", v[1], NULL};
	// int	i;

	// i = 0;
	char	*c;
	// while (s[i])
	// {
	// 	printf("%s\n", s[i]);
	// 	i++;
	// }
	// if (c != 1)
	// 	perror("too much arguments arguments");
	// int	i = execve(s[0], s, env);
	// (void)c;
	// printf("%s\n", s[0]);
	(void)env;
	(void)c;
	(void)v;
	// (void)env;
	// printf("%d", c);
	// if (ls_exe(s, env) == 1)
	// 	return (1);
	while (1)
	{
		c = readline(0);
		wait
	}
	return (0);
}
