/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/03/17 18:14:16 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	init_prompt(char **v)
// {
// 	int		i;
// 	char	*buff;

// 	i = 0;
// 	(void)v;
// 	(void)env;
// 	while (1)
// 	{
// 		buff = readline("minishell>:$");
// 		add_history(buff);
// 		excute_command(buff, env);
// 	}
// }

t_input	*lex_input(char **str)
{
	t_input	*ret;
	int		i;

	ret = NULL;
	i = 0;
	while (str[i])
	{
		if (is_operator(str[i]))
			ft_lstaddback(&ret, ft_lstnew(str[i]));
		else if (is_literal())
		i++;
	}
}


int	main(int c, char **v, char **env)
{
	char	**str;
	int		i;
	t_input	*d;

	i = 0;
	(void)c;
	(void)v;
	(void)env;
	str = ft_split(v[1], ' ');
	d = lex_input(str);
	return (0);
}
