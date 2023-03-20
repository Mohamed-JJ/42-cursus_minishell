/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:50:42 by mjarboua          #+#    #+#             */
/*   Updated: 2023/03/20 14:32:06 by mjarboua         ###   ########.fr       */
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

void	ft_lstadd_back(t_input **lst, t_input *new)
{
	t_input	*node;

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

t_input	*ft_lstnew(char	*content, int type)
{
	t_input	*new;

	new = malloc(sizeof(t_input));
	if (!new)
		return (NULL);
	new->str = content;
	if (type == 0)
	{
		new->literal = 1;
		new->op = 0;
	}
	else
	{
		new->literal = 0;
		new->op = 1;
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
