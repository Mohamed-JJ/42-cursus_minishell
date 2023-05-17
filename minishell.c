/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/17 20:31:33 by mjarboua         ###   ########.fr       */
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
						// execution1(headd,cmd, env);
						t_cmd *tmp = cmd;
						
						while (tmp)
						{
							if (tmp->h_i == 0)
								printf("priority = heredoc\n");
							else
								printf("priority = infile\n");
							if (cmd->command)
								printf("cmd->type = %s\n", tmp->command);
							if (cmd->args)
								for (size_t i = 0; cmd->args[i]; i++)
								{
									printf("cmd->args[%zu] = %s\n", i, cmd->args[i]);
								}
							if (cmd->infile)
								for (size_t i = 0; cmd->infile[i]; i++)
								{
									printf("cmd->infile[%zu] = %s\n", i, cmd->infile[i]);
								}
							if (cmd->outfile)
								for (size_t i = 0; cmd->outfile[i]; i++)
								{
									printf("cmd->outfile[%zu] = %s\n", i, cmd->outfile[i]);
								}
							if (cmd->heredoc_del)
								for (size_t i = 0; cmd->heredoc_del[i]; i++)
								{
									printf("cmd->heredoc_del[%zu] = %s\n", i, cmd->heredoc_del[i]);
								}	
							tmp = tmp->next;							
						}
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
