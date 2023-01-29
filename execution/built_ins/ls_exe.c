/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:07:24 by mjarboua          #+#    #+#             */
/*   Updated: 2023/01/29 20:48:22 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ls_exe(char **s, char **env)
{
	if (!env)
		return (perror("ERROR !!!\n"), 1);
	if (!s)
		return (perror("ERROR !!!\n"), 1);
	execve(s[0], s, env);
	return (0);}
