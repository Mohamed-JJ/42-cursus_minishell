/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/19 21:01:47 by imaaitat         ###   ########.fr       */
=======
/*   Updated: 2023/05/19 18:46:17 by mjarboua         ###   ########.fr       */
>>>>>>> a0f23b160a558bd3f2551ca6f5ed61a07e0de8b3
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
	t_env *head;
<<<<<<< HEAD
  	head = set_env(env, head);

=======
  	head = NULL;
>>>>>>> a0f23b160a558bd3f2551ca6f5ed61a07e0de8b3
	while (1)
	{
		input = readline("minishell$>");
		if (!input)
		{
			printf("exit");
			exit(0);
		}
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
<<<<<<< HEAD
						execution1(head,cmd, env);
=======
>>>>>>> a0f23b160a558bd3f2551ca6f5ed61a07e0de8b3
						if (cmd)
							free_cmd_list(cmd);
					}
				}
			}
		}
		
		free(input);
		input = NULL;
	}
	free_env(head);
	return (0);
}
