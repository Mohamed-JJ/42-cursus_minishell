/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:33:48 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/29 17:52:38 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

char	*expand_var(char *s, t_env *env)
{
	t_data	h;
	char	*ret;

	ret = NULL;
	h.i = -1;
	h.j = 0;
	while (s[++h.i])
	{
		if (s[h.i] == '\'')
			handle_single_quote(s, &h, &ret, env);
		else if (s[h.i] == '\"')
			handle_double_quote(s, &ret, env, &h);
		else if (s[h.i] == '$')
			handle_dollar(s, &h, &ret, env);
		else if (s[h.i] == '<')
			handle_heredoc(s, &h, &ret);
		else
			ret = ft_strjoin_parsing_characters(ret, s[h.i]);
		if (h.j == 1)
			return (free_string(&ret), free_string(&s), NULL);
		if (!s[h.i])
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
