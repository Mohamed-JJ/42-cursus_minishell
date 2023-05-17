/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/17 18:45:54 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int c, char **v, char **env)
{
	t_lex	*lex;
	char	*input;
	t_cmd	*cmd;

	lex = NULL;
	(void)c;
	(void)v;
	while (1)
	{
		input = readline("minishell$>");
		if (!input)
			exit(0);
		if (ft_strlen_parsing(input) > 0)
		{
			add_history(input);
			input = expand_var(input, env);
			if (input)
			{
				input = insert_spaces(input);
				lex = lexer(input);
				if (lex)
				{
					assign_type(lex);
					manage_type(lex);
					if (generate_error(lex))
						free_list(&lex);
					else
					{
						cmd = create_cmd(lex);
						if (lex)
							free_list(&lex);
						if (cmd)
							free_cmd_list(cmd);
					}
				}
			}
		}
		free(input);
		input = NULL;
	}
	return (0);
}
