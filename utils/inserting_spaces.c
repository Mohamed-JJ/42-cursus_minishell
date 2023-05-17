/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inserting_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:36:23 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/17 15:12:00 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	insert_space_inside_quotes(char *input, int *i, char **ret)
{
	char	character;

	character = input[*i];
	*ret = ft_strjoin_parsing_characters(*ret, input[(*i)++]);
	while (input[*i] != character && input[*i])
		*ret = ft_strjoin_parsing_characters(*ret, input[(*i)++]);
	*ret = ft_strjoin_parsing_characters(*ret, input[*i]);
}

void	insert_space_between_op(char *input, int *i, char **ret)
{
	char	character;

	character = input[*i];
	*ret = ft_strjoin_parsing_characters(*ret, ' ');
	while (input[*i] == character && input[*i])
	{
		if (input[*i + 1] != character)
			break ;
		*ret = ft_strjoin_parsing_characters(*ret, input[(*i)++]);
	}
	*ret = ft_strjoin_parsing_characters(*ret, input[*i]);
	*ret = ft_strjoin_parsing_characters(*ret, ' ');
}

char	*insert_spaces(char *input)
{
	int		i;
	char	*ret;

	i = -1;
	ret = NULL;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			insert_space_inside_quotes(input, &i, &ret);
		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
			insert_space_between_op(input, &i, &ret);
		else
			ret = ft_strjoin_parsing_characters(ret, input[i]);
	}
	printf("ret = |%s|\n", ret);
	return (free(input), input = NULL, ret);
}
