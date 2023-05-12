/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:11:27 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/12 18:31:00 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_string(char **str)
{
	free(*str);
	*str = NULL;
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
