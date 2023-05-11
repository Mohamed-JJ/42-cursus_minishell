/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:54:35 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/11 12:50:02 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	handle_double_quote(char *s, char **ret, char **env, int *i)
{
	printf("%p\t%p\n", s, *ret);
	*ret = ft_strjoin_characters(*ret, s[*i]);
	(*i)++;
	while (s[*i] && s[*i] != '\"')
	{
		if (s[*i] == '$' && s[*i + 1] != '\"'
			&& s[*i + 1] != ' ' && s[*i + 1] != '\t')
			handle_env(s, ret, env, i);
		else
			*ret = ft_strjoin_characters(*ret, s[*i]);
		if (s[*i] == '\"' || !s[*i])
			break ;
		(*i)++;
	}
	if (!s[*i])
		printf("minishell : error in quotation\n");
	else if (s[*i] == '\"')
		*ret = ft_strjoin_characters(*ret, s[*i]);
	(*i)++;
	if (s[*i] == '\"')
		handle_double_quote(s, ret, env, i);
	else
		*ret = ft_strjoin_characters(*ret, s[*i]);
}

void	handle_single_quote(char *s, int *i, char **ret)
{
	*ret = ft_strjoin_characters(*ret, s[*i]);
	(*i)++;
	while (s[*i] && s[*i] != '\'')
	{
		*ret = ft_strjoin_characters(*ret, s[*i]);
		(*i)++;
	}
	if (!s[*i])
		printf("minishell : error in quotation\n");
	else
		*ret = ft_strjoin_characters(*ret, s[*i]);
	(*i)++;
	if (s[*i] == '\'')
		handle_single_quote(s, i, ret);
	else
		*ret = ft_strjoin_characters(*ret, s[*i]);
}

void	handle_dollar(char *s, int *i, char **ret, char **env)
{
	char	*tmp;
	char	*holder;

	tmp = NULL;
	holder = NULL;
	if (s[*i] == '$' && s[*i + 1] != ' ' && s[*i + 1] != '\t' && s[*i + 1])
	{
		(*i)++;
		while (s[*i] && ft_isalnum(s[*i]))
		{
			tmp = ft_strjoin_characters(tmp, s[*i]);
			if (!s[*i + 1] || s[*i + 1] == ' '
				|| s[*i + 1] == '\t' || !ft_isalnum(s[*i + 1]))
				break ;
			(*i)++;
		}
		holder = get_env(env, tmp);
		*ret = ft_strjoin(*ret, holder, 1);
		free(tmp);
		tmp = NULL;
		holder = NULL;
	}
	else
		*ret = ft_strjoin_characters(*ret, s[*i]);
}

void	handle_heredoc(char *s, int *i, char **ret)
{
	while (s[*i] && s[*i] == '<')
	{
		*ret = ft_strjoin_characters(*ret, s[*i]);
		(*i)++;
	}
	(*i)--;
	while (s[*i] && s[*i] == ' ')
	{
		*ret = ft_strjoin_characters(*ret, s[*i]);
		(*i)++;
	}
	while (s[*i])
	{
		if (ft_strchr("|>< ", s[*i]))
			break ;
		*ret = ft_strjoin_characters(*ret, s[*i]);
		(*i)++;
	}
}

void	handle_env(char	*s, char **ret, char **env, int *i)
{
	char	*tmp;
	char	*holder;

	tmp = NULL;
	holder = NULL;
	while (s[*i] && s[*i] == '$')
		(*i)++;
	while (s[*i] && ft_isalnum(s[*i]))
	{
		tmp = ft_strjoin_characters(tmp, s[*i]);
		if (!ft_isalnum(s[*i + 1]) || !s[*i + 1])
			break ;
		(*i)++;
	}
	holder = get_env(env, tmp);
	*ret = ft_strjoin(*ret, holder, 1);
	free(tmp);
	tmp = NULL;
	holder = NULL;
}
