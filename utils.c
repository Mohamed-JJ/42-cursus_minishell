/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:50:42 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/28 14:16:45 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./lexer/lexer.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == '_')
		return (1);
	else
		return (0);
}

void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
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

char	*ft_strjoin_characters(char *s1, char character)
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

// t_cmd	*ft_lstnew(char	**content, int status)
// {
// 	t_cmd	*new;
// 	int		i;
// 	int		x;

// 	i = 0;
// 	x = 0;
// 	new = malloc(sizeof(t_cmd));
// 	if (!new)
// 		return (NULL);
// 	if (status == 0)
// 		new->cmd = *content;
// 	else if (status == 1)
// 	{
// 		i = arr_len(content);
// 		new->args = malloc(sizeof(char *) * i);
// 		while (content[x])
// 		{
// 			new->args[x] = ft_strdup(content[x]);
// 			x++;
// 		}
// 		new->args[x] = NULL;
// 	}
// 	new->next = NULL;
// 	return (new);
// }

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
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
    return (*(unsigned char*)s1 - *(unsigned char*)s2);
}


int	check_if_operator(char *str)
{
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

int	skip_special_characters(char *str, int *i, char c)
{
	while (str[*i] && str[*i] == c)
		(*i)++;
	return (2);
}

void	dqoute_handler(char *str, t_data *data, t_lex **lex)
{
	data->i++;
	while (str[data->i] && str[data->i] != '\"')
	{
		data->s = ft_strjoin_characters(data->s, str[data->i]);
		data->i++;
	}
	if (!str[data->i])
		printf("error in quotation\n");
	data->i++;
	if (str[data->i] == '\"')
		dqoute_handler(str, data, lex);
	else
		ft_lstadd_back_lexer(lex, new_lex(data->s, WORD));
}

void	dqoute_handler_expander(char *str, t_data *data)
{
	data->i++;
	while (str[data->i] && str[data->i] != '\"')
	{
		data->s = ft_strjoin_characters(data->s, str[data->i]);
		data->i++;
	}
	if (!str[data->i])
		printf("error in quotation\n");
	data->i++;
	if (str[data->i] == '\"')
		dqoute_handler_expander(str, data);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	c;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	str = malloc((ft_strlen(s1)
				+ ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	c = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[c] != '\0')
		str[i++] = s2[c++];
	str[i] = '\0';
	return (free(s1), str);
}

void	print_list(t_lex *lex)
{
	while (lex)
	{
		if (lex->type == COMMAND)
			printf("%s is a command\n", lex->str);
		else if (lex->type == PIPE)
			printf("%s is a pipe\n", lex->str);
		else if (lex->type == REDIRECT)
			printf("%s is a redirect\n", lex->str);
		else if (lex->type == HEREDOC)
			printf("%s is a heredoc\n", lex->str);
		else if (lex->type == APPEND)
			printf("%s is a append\n", lex->str);
		else if (lex->type == IN_FILE)
			printf("%s is a input file\n", lex->str);
		else if (lex->type == OUT_FILE)
			printf("%s is a output file\n", lex->str);
		else if (lex->type == READ_INPUT)
			printf("%s is a read input\n", lex->str);
		else if (lex->type == HEREDOC_DEL)
			printf("%s is a heredoc delimiter\n", lex->str);
		else
			printf("%s is an word\n", lex->str);
		lex = lex->next;
	}
}