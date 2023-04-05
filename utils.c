/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:50:42 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/05 21:02:44 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

char	*ft_strjoin(char *s1, char character)
{
	size_t	i;
	size_t	c;
	char	*str;

	if (!s1 && !character)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	str = malloc(ft_strlen(s1) + 2 * sizeof(char));
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

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(s1);
	s2 = malloc((size + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (s + i);
		i++;
	}
	return (NULL);
}

int	ft_isdigit(int c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (1);
}

int	ft_isalpha(int c)
{
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
		return (0);
	return (1);
}

void	ft_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*node;

	node = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

int  arr_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_cmd	*ft_lstnew(char	**content, int status)
{
	t_cmd	*new;
	int		i;
	int		x;

	i = 0;
	x = 0;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	if (status == 0)
		new->cmd = *content;
	else if (status == 1)
	{
		i = arr_len(content);
		new->args = malloc(sizeof(char *) * i);
		while (content[x])
		{
			new->args[x] = ft_strdup(content[x]);
			x++;
		}
		new->args[x] = NULL;
	}
	new->next = NULL;
	return (new);
}

int	ft_isprint(int c)
{
	if (!(c >= 32 && c <= 126))
		return (0);
	return (1);
}

char	*ft_substr(char *s, int start, int len)
{
	int	j;
	char	*str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) == 0 || len <= 0)
		return (ft_strdup(""));
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	while (j < len && s[start])
	{
		str[j++] = s[start++];
	}
	str[j] = '\0';
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}
