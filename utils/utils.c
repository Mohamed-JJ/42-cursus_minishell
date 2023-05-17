/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:50:42 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/17 18:58:40 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"
#include "../includes/lexer.h"

void	get_until_equal(char *s, int *len)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	*len = i;
}

char	*get_env(char **env, char *s)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = 0;
	ret = NULL;
	while (env[i])
	{
		get_until_equal(env[i], &len);
		if (!ft_strncmp_parsing(env[i], s, ft_strlen_parsing(s)) && len == ft_strlen_parsing(s))
		{
			ret = ft_strdup_parsing(env[i] + ft_strlen_parsing(s) + 1);
			break ;
		}
		i++;
	}
	return (ret);
}

int	ft_isalnum_parsing(int c)
{
	if ((c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == '_')
		return (1);
	else
		return (0);
}


int	ft_strlen_parsing(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}


