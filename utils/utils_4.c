/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:50:28 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/17 18:48:23 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

int	ft_strncmp_parsing(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

void	fill_array(char **ret, int type, char *s)
{
	if (type == ARGUMENT)
	{
		ret[0] = ft_strjoin_parsing(ret[0], s, 0);
		ret[0] = ft_strjoin_parsing(ret[0], " ", 0);
	}
	else if (type == OUT_FILE)
	{
		ret[1] = ft_strjoin_parsing(ret[1], s, 0);
		ret[1] = ft_strjoin_parsing(ret[1], " ", 0);
	}
	else if (type == IN_FILE)
	{
		ret[2] = ft_strjoin_parsing(ret[2], s, 0);
		ret[2] = ft_strjoin_parsing(ret[2], " ", 0);
	}
	else if (type == HEREDOC_DEL)
	{
		ret[3] = ft_strjoin_parsing(ret[3], s, 0);
		ret[3] = ft_strjoin_parsing(ret[3], " ", 0);
	}
	check_arr(ret);
}

char	**empty_array(void)
{
	int		i;
	char	**files;

	i = 0;
	files = malloc(sizeof(char *) * 5);
	if (!files)
		return (NULL);
	while (i <= 4)
	{
		files[i] = NULL;
		i++;
	}
	return (files);
}

char	**fill_arrays(char *ar)
{
	char	**cpy;
	int		i;

	i = 0;
	if (!ar || ft_strlen_parsing(ar) == 0)
		cpy = NULL;
	else
		cpy = ft_split_parsing(ar, '\n');
	return (cpy);
}

char	*ft_strjoin_parsing_characters(char *s1, char character)
{
	size_t	i;
	size_t	c;
	char	*str;

	if (!s1 && !character)
		return (NULL);
	if (!s1)
		s1 = ft_strdup_parsing("");
	str = malloc(ft_strlen_parsing(s1) + 2 * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	c = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	str[i] = character;
	str[++i] = '\0';
	return (free(s1), str);
}
