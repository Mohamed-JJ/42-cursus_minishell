/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/26 15:27:55 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/structs.h"
#include "includes/utils.h"
#include "libft/libft.h"
#include <unistd.h>

static char	**get_cwd(void)
{
	char	**env;
	char	cwd[1024];
	char	*path;

	path = ft_strdup("/Users/imaaitat/.brew/bin:/Users/imaaitat/goinfre/homebrew/bin:\
	/Users/imaaitat/goinfre/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:\
	/Library/Frameworks/Mono.framework/Versions/Current/Commands");
	getcwd(cwd, sizeof(cwd));
	env = (char **)malloc(sizeof(char *) * 5);
	env[0] = ft_strjoin_parsing(ft_strdup("PWD="), cwd, 0);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = ft_strjoin(ft_strdup("rix="), path);
	env[4] = NULL;
	free(path);
	return (env);
}

void	create_command_and_execute(t_lex **lex, t_env **envh, char **env)
{
	t_cmd	*cmd;

	if (lex)
	{
		assign_type(*lex);
		manage_type(*lex);
		if (generate_error(*lex))
			free_list(lex);
		else
		{
			cmd = create_cmd(*lex);
			if (lex)
				free_list(lex);
			execution1(envh, cmd, env);
			if (cmd)
				free_cmd_list(cmd);
		}
	}
}

void	prompt(t_env **envh, char **env)
{
	t_lex	*lex;
	char	*input;
	t_cmd	*cmd;

	lex = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	rl_catch_signals = 0;
	input = readline("minishell🥀>");
	if (!input)
		return (printf("exit\n"), exit(1));
	if (ft_strlen(input) > 0)
	{
		add_history(input);
		input = expand_var(input, *envh);
		if (input)
		{
			input = insert_spaces(input);
			lex = lexer(input);
			create_command_and_execute(&lex, envh, env);
		}
	}
	free(input);
	input = NULL;
}

int	main(int c, char **v, char **env)
{
	t_env	*envh;
	int		in;

	(void)v;
	if (c > 1)
		return (printf("No arguments needed\n"), 1);
	if (env[0] == NULL)
		env = get_cwd();
	envh = set_env(env, envh);
	change_shell_level(env);
	in = dup(0);
	while (1)
	{
		dup2(in, 0);
		prompt(&envh, env);
	}
	free_env(envh);
	return (0);
}
