/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:50:42 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/11 15:55:57 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"
#include "../includes/lexer.h"

char	*get_env(char **env, char *s)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], s, ft_strlen(s)))
		{
			ret = ft_strdup(env[i] + ft_strlen(s) + 1);
			break ;
		}
		i++;
	}
	return (ret);
}

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

void	print_list(t_lex *lex)
{
	t_lex *tmp;

	tmp = lex;
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
	lex = tmp;
}


