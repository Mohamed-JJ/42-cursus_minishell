/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:47:37 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/17 18:54:45 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

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

char	*ft_strjoin_parsing(char *s1, char *s2, int _free)
{
	size_t	i;
	size_t	c;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup_parsing("");
	if (!s2)
		s2 = ft_strdup_parsing("");
	str = malloc((ft_strlen_parsing(s1)
				+ ft_strlen_parsing(s2) + 1) * sizeof(char));
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
	if (_free)
		free(s2);
	return (free(s1), str);
}

int	skip_special_characters(char *str, int *i, char c)
{
	while (str[*i] && str[*i] == c)
		(*i)++;
	return (2);
}

void	dqoute_handler(char *str, t_data *data, t_lex **lex, int flag)
{
	static int	f;
	data->c = str[data->i];
	data->i++;
	while (str[data->i] && str[data->i] != data->c)
	{
		data->s = ft_strjoin_parsing_characters(data->s, str[data->i]);
		printf("of the ittereation %d character %c is del and str is  %s\n", f, data->c, data->s);
		data->i++;
	}
	if (!str[data->i])
		printf("error in quotation |%c|\n", str[data->i]);
	data->i++;
	f++;
	if ((str[data->i] == '\'' || str[data->i] == '\"'))
		dqoute_handler(str, data, lex, 1);
	else if (str[data->i] == ' ' || str[data->i] == '\t' || !str[data->i])
	{
		if (data->s && flag == 1)
			ft_lstadd_back_lexer(lex, new_lex(data->s, WORD, 1));
		// free(data->s);
	}
}
