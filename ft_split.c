/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:55:28 by mjarboua          #+#    #+#             */
/*   Updated: 2023/03/20 14:32:00 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	w_counter(char *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i] != '\0')
			counter++;
		while (s[i] != c && s[i])
			i++;
	}
	return (counter);
}

static char	**free_all(char **str, int c)
{
	if (!str)
	{
		while (0 <= c)
		{
			c--;
			free (str[c]);
			str[c] = 0;
		}
		free (str);
		str = 0;
	}
	return (NULL);
}

static char	**allocate(char **str, char *s, char c)
{
	int	start;
	int	end;
	int	i;

	i = 0;
	start = 0;
	while (i < w_counter((char *)s, c))
	{
		while (s[start] == c && s[start] != '\0')
			start++;
		end = start;
		while (s[end] != c && s[end] != '\0')
			end++;
		str[i] = ft_substr((char *)s, start, end - start);
		if (!str[i])
			return (free_all(str, i));
		i++;
		start = end;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char *s, char c)
{
	char	**str;

	if (!s)
		return (0);
	str = (char **)malloc((w_counter((char *)s, c) + 1) * sizeof(char *));
	if (!str)
		return (0);
	str = allocate(str, (char *)s, c);
	return (str);
}
