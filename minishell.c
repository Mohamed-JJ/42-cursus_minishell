/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/22 19:10:54 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/structs.h"
#include "includes/utils.h"
#include <signal.h>
#include <unistd.h>

static char **get_cwd(void)
{
	char	**env;
	char	cwd[1024];
	getcwd(cwd, sizeof(cwd));
	env = (char **)malloc(sizeof(char *) * 4);
	env[0] = ft_strjoin_parsing(ft_strdup("PWD="), cwd, 0);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	return (env);
}

void	prompt(t_env **envh, char **env)
{
	t_lex	*lex;
	char	*input;
	t_cmd	*cmd;
int pid;
pid = fork();
if (pid == 0)
{
	signal(SIGINT, signal_handler);
	while (1) {
	lex = NULL;
	input = readline("minishell🥀>");
	
	if (!input)
		exit(130);
	if (ft_strlen(input) > 0)
	{
		add_history(input);
		input = expand_var(input, *envh);
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
					execution1(*envh,cmd, env);
					if (cmd)
						free_cmd_list(cmd);
				}
			}
		}
	}
	free(input);
	input = NULL;
	}
}
}


int	main(int c, char **v, char **env)
{
	t_env *envh;

	(void)v;
	if (c > 1)
		return (printf("No arguments needed\n"), 1);
	if (env[0] == NULL) 
		env = get_cwd();
  	envh = set_env(env, envh);
    change_shell_level(env);
	signal(SIGINT, signal_handler2);
	while (1)
	{
		prompt(&envh, env);
		waitpid(-1, &status, 0);
   		status = WEXITSTATUS(status);
		if (status == 130)
			printf("exit\n"), exit(130);
		
	}
		
	free_env(envh);
	return (0);
}
