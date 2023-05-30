/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:54:35 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/29 22:46:40 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_double_quote(char *s, char **ret, t_env *env, t_data *h)
{
	t_env	*tmp;

	tmp = env;
	*ret = ft_strjoin_parsing_characters(*ret, s[h->i++]);
	while (s[h->i] && s[h->i] != '\"')
	{
		if (s[h->i] == '$' && s[h->i + 1] != '\"' && s[h->i + 1] != ' '
			&& s[h->i + 1] != '\t')
			handle_env(s, ret, env, h);
		else
			*ret = ft_strjoin_parsing_characters(*ret, s[h->i]);
		(h->i)++;
	}
	if (!s[h->i])
		return (h->j = 1, (void)printf("minishell : error in quotation\n"));
	else
		handle_double_quote_2(s, ret, env, h);
}

void	handle_single_quote(char *s, t_data *h, char **ret, t_env *env)
{
	*ret = ft_strjoin_parsing_characters(*ret, s[h->i]);
	h->i++;
	while (s[h->i] && s[h->i] != '\'')
	{
		*ret = ft_strjoin_parsing_characters(*ret, s[h->i]);
		h->i++;
	}
	if (!s[h->i])
		return (h->j = 1, g_status = 258,
			(void)printf("minishell : error in quotation\n"));
	else
		*ret = ft_strjoin_parsing_characters(*ret, s[h->i]);
	(h->i)++;
	if (s[h->i] == '\'')
		handle_single_quote(s, h, ret, env);
	else if (s[h->i] == '$')
		handle_dollar(s, h, ret, env);
	else if (s[h->i] == '\"')
		handle_double_quote(s, ret, env, h);
	else
		*ret = ft_strjoin_parsing_characters(*ret, s[h->i]);
}

void	handle_dollar(char *s, t_data *h, char **ret, t_env *env)
{
	char	*tmp;
	char	*holder;

	tmp = NULL;
	holder = NULL;
	if (s[h->i + 1] == '\'' || s[h->i + 1] == '\"')
		return ;
	if (s[h->i] == '$' && s[h->i + 1] != ' ' && s[h->i + 1])
	{
		while (s[h->i++])
		{
			tmp = ft_strjoin_parsing_characters(tmp, s[h->i]);
			if (s[h->i + 1] && s[h->i + 1] == '?' && s[h->i] == '$')
				tmp = ft_strjoin_parsing_characters(tmp, s[h->i]);
			else if (!s[h->i + 1] || s[h->i + 1] == ' ' || s[h->i + 1] == '\t'
				|| !ft_isalnum_parsing(s[h->i + 1]))
				break ;
		}
		holder = get_env(&env, tmp);
		*ret = ft_strjoin_parsing(*ret, holder, 1);
		free_string(&tmp);
		holder = NULL;
	}
	else
		*ret = ft_strjoin_parsing_characters(*ret, s[h->i]);
}

void	handle_heredoc(char *s, t_data *h, char **ret)
{
	while (s[h->i] && s[h->i] == '<')
	{
		*ret = ft_strjoin_parsing_characters(*ret, s[h->i]);
		h->i++;
	}
	*ret = ft_strjoin_parsing_characters(*ret, ' ');
	while (s[h->i] && s[h->i] == ' ')
	{
		*ret = ft_strjoin_parsing_characters(*ret, s[h->i]);
		h->i++;
	}
	while (s[h->i])
	{
		if (ft_strchr_parsing("|>< ", s[h->i]))
			break ;
		*ret = ft_strjoin_parsing_characters(*ret, s[h->i]);
		h->i++;
	}
	*ret = ft_strjoin_parsing_characters(*ret, s[h->i]);
}

void	handle_env(char *s, char **ret, t_env *env, t_data *h)
{
	char	*tmp;
	char	*holder;

	tmp = NULL;
	holder = NULL;
	while (s[h->i] && s[h->i] == '$')
		h->i++;
	while (s[h->i])
	{
		tmp = ft_strjoin_parsing_characters(tmp, s[h->i]);
		if (s[h->i + 1] && s[h->i + 1] == '?' && s[h->i] == '$')
			tmp = ft_strjoin_parsing_characters(tmp, s[h->i]);
		else if (!ft_isalnum_parsing(s[h->i + 1]) || !s[h->i + 1])
			break ;
		h->i++;
	}
	holder = get_env(&env, tmp);
	*ret = ft_strjoin_parsing(*ret, holder, 1);
	free(tmp);
	tmp = NULL;
	holder = NULL;
}
