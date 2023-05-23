/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:50:42 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/21 17:40:08 by imaaitat         ###   ########.fr       */
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

char	*get_env(t_env **env, char *s)
{
	t_env	*tmp;
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, s))
		{
			if (ft_strlen(tmp->value) > 0)
				ret = ft_strdup_parsing(tmp->value + 1);
			break ;
		}
		tmp = tmp->next;
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


