/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/18 12:36:42 by imaaitat         ###   ########.fr       */
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
	t_env *headd;
	t_env *head;
  	head = NULL;
  	headd = set_env(env, head);
	while (1)
	{
		input = readline("minishell$>");
		if (!input)
			exit(0);
		if (ft_strlen(input) > 0)
		{
			input[ft_strlen(input)] = '\0';
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
						execution1(headd,cmd, env);
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
