/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:54:35 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/20 13:05:44 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_double_quote(char *s, char **ret, char **env, int *i)
{
	*ret = ft_strjoin_parsing_characters(*ret, s[*i]);
	(*i)++;
	while (s[*i] && s[*i] != '\"')
	{
		if (s[*i] == '$' && s[*i + 1] != '\"'
			&& s[*i + 1] != ' ' && s[*i + 1] != '\t')
			handle_env(s, ret, env, i);
		else
			*ret = ft_strjoin_parsing_characters(*ret, s[*i]);
		(*i)++;
	}
	if (!s[*i])
		return (printf("minishell : error in quotations\n"), 1);
	else if (s[*i] == '\"')
		*ret = ft_strjoin_parsing_characters(*ret, s[*i]);
	(*i)++;
	if (s[*i] == '\"')
		handle_double_quote(s, ret, env, i);
	else if (s[*i] == '\'')
		handle_single_quote(s, i, ret, env);
	else
		*ret = ft_strjoin_parsing_characters(*ret, s[*i]);
	return (0);
}

int	handle_single_quote(char *s, int *i, char **ret, char **env)
{
	*ret = ft_strjoin_parsing_characters(*ret, s[*i]);
	(*i)++;
	while (s[*i] && s[*i] != '\'')
	{
		*ret = ft_strjoin_parsing_characters(*ret, s[*i]);
		(*i)++;
	}
	if (!s[*i])
		return (printf("minishell : error in quotation\n"), 1);
	else
		*ret = ft_strjoin_parsing_characters(*ret, s[*i]);
	(*i)++;
	if (s[*i] == '\'')
		handle_single_quote(s, i, ret, env);
	else if (s[*i] == '\"')
		handle_double_quote(s, ret, env, i);
	else
		*ret = ft_strjoin_parsing_characters(*ret, s[*i]);
	return (0);
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
		while (s[*i] && ft_isalnum_parsing(s[*i]))
		{
			tmp = ft_strjoin_parsing_characters(tmp, s[*i]);
			if (!s[*i + 1] || s[*i + 1] == ' '
				|| s[*i + 1] == '\t' || !ft_isalnum_parsing(s[*i + 1]))
				break ;
			(*i)++;
		}
		holder = get_env(env, tmp);
		*ret = ft_strjoin_parsing(*ret, holder, 1);
		free(tmp);
		tmp = NULL;
		holder = NULL;
	}
	else
		*ret = ft_strjoin_parsing_characters(*ret, s[*i]);
}

void	handle_heredoc(char *s, int *i, char **ret)
{
	while (s[*i] && s[*i] == '<')
	{
		*ret = ft_strjoin_parsing_characters(*ret, s[*i]);
		(*i)++;
	}
	(*i)--;
	while (s[*i] && s[*i] == ' ')
	{
		*ret = ft_strjoin_parsing_characters(*ret, s[*i]);
		(*i)++;
	}
	while (s[*i])
	{
		if (ft_strchr_parsing("|>< ", s[*i]))
			break ;
		*ret = ft_strjoin_parsing_characters(*ret, s[*i]);
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
	while (s[*i] && ft_isalnum_parsing(s[*i]))
	{
		tmp = ft_strjoin_parsing_characters(tmp, s[*i]);
		if (!ft_isalnum_parsing(s[*i + 1]) || !s[*i + 1])
			break ;
		(*i)++;
	}
	holder = get_env(env, tmp);
	*ret = ft_strjoin_parsing(*ret, holder, 1);
	free(tmp);
	tmp = NULL;
	holder = NULL;
}
