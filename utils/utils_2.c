/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:33:48 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/21 16:41:46 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

char	*expand_var(char *s, t_env *env)
{
	int		i;
	int		r;
	char	*ret;

	ret = NULL;
	i = -1;
	r = 0;
	while (s[++i])
	{
		if (s[i] == '\'')
			r = handle_single_quote(s, &i, &ret, env);
		else if (s[i] == '\"')
			r = handle_double_quote(s, &ret, env, &i);
		else if (s[i] == '$')
			handle_dollar(s, &i, &ret, env);
		else if (s[i] == '<')
			handle_heredoc(s, &i, &ret);
		else
			ret = ft_strjoin_parsing_characters(ret, s[i]);
		if (r == 1)
			return (free_string(&ret), free_string(&s), NULL);
		if (!s[i])
			break ;
	}
	return (free(s), s = NULL, ret);
}

char	*ft_substr_parsing(char *s, int start, int len)
{
	int		j;
	char	*str;

	if (!s)
		return (NULL);
	if (ft_strlen_parsing(s) == 0 || len <= 0)
		return (ft_strdup_parsing(""));
	if (start > ft_strlen_parsing(s))
		return (ft_strdup_parsing(""));
	if (len > ft_strlen_parsing(s + start))
		len = ft_strlen_parsing(s + start);
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

int	ft_isprint(int c)
{
	if (!(c >= 32 && c <= 126))
		return (0);
	return (1);
}

int	arr_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	skip_whitespaces(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	(*i)--;
}
