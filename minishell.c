/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/13 15:38:52 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*insert_spaces(char *input)
{
	int		i;
	char	*ret;
	char	character;

	i = -1;
	ret = NULL;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			character = input[i];
			ret = ft_strjoin_characters(ret, input[i++]);
			while (input[i] != character && input[i])
				ret = ft_strjoin_characters(ret, input[i++]);
			ret = ft_strjoin_characters(ret, input[i]);
		}
		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			character = input[i];
			ret = ft_strjoin_characters(ret, ' ');
			while (input[i] == character && input[i])
			{
				if (input[i + 1] != character)
					break ;
				ret = ft_strjoin_characters(ret, input[i++]);
			}
			ret = ft_strjoin_characters(ret, input[i]);
			ret = ft_strjoin_characters(ret, ' ');
		}
		else
			ret = ft_strjoin_characters(ret, input[i]);
	}
	return (free(input), input = NULL, ret);
}

t_cmd	*new_command(char *str, char **arr, int i)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (NULL);
	ret->command = ft_strdup(str);
	ret->args = fill_arrays(arr[0]);
	ret->outfile = fill_arrays(arr[1]);
	ret->infile = fill_arrays(arr[2]);
	ret->heredoc_del = fill_arrays(arr[3]);
	ret->in_out = i;
	ret->next = NULL;
	return (ret);
}
// {
// 	t_cmd	*ret;

// 	ret = malloc(sizeof(t_cmd));
// 	if (!ret)
// 		return (NULL);
// 	ret->command = ft_strdup(p->s);
// 	ret->args = fill_arrays(p->arr[0]);
// 	ret->outfile = fill_arrays(p->arr[1]);
// 	ret->infile = fill_arrays(p->arr[2]);
// 	ret->heredoc_del = fill_arrays(p->arr[3]);
// 	ret->in_out = p->i;
// 	return (ret);
// }


void	ft_lstadd_back_cmd(t_cmd **c, t_cmd *new)
{
	t_cmd	*tmp;

	if (!c)
		return ;
	if (!*c)
	{
		*c = new;
		return ;
	}
	tmp = *c;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_cmd	*fill_till_eol_pipe(char **str, char **arr, t_lex **s)
{
	int	i;

	i = 0;
	while (*s && (*s)->type != PIPE)
	{
		redirection_type((*s)->type, &i);
		if ((*s)->type == COMMAND)
			*str = ft_strjoin(*str, (*s)->str, 0);
		else if ((*s)->type == ARGUMENT)
			arr[0] = join_string((*s)->str, &arr[0]);
		else if ((*s)->type == OUT_FILE)
			arr[1] = join_string((*s)->str, &arr[1]);
		else if ((*s)->type == IN_FILE)
			arr[2] = join_string((*s)->str, &arr[2]);
		else if ((*s)->type == HEREDOC_DEL)
			arr[3] = join_string((*s)->str, &arr[3]);
		*s = (*s)->next;
	}
	if (*s && (*s)->type == PIPE)
		puts("current is pipes");
	return (new_command(*str, arr, i));
}

t_cmd	*create_cmd(t_lex *s)
{
	char	**arr;
	char	*str;
	t_cmd	*ret;

	ret = NULL;
	arr = NULL;
	while (s)
	{
		str = NULL;
		arr = empty_array();
		puts("loop");
		ft_lstadd_back_cmd(&ret, fill_till_eol_pipe(&str, arr, &s));
		if (str)
			free_string(&str);
		if (arr)
		{
			for (int i = 0; i < 4; i++)
			{
				printf("arr[%d] = %s\n", i, arr[i]);
				free(arr[i]);
				arr[i] = NULL;
			}
			free(arr);
			arr = NULL;
		}
		if (s == NULL)
			break ;
		s = s->next;
	}
	return (ret);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void	free_list(t_lex	**list)
{
	if (list && *list)
	{
		while (*list)
		{
			free((*list)->str);
			free(*list);
			if ((*list)->next == NULL)
				break ;
			*list = (*list)->next;
		}
		*list = NULL;
	}
}

void free_cmd_list(t_cmd *cmd)
{
	int i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->next)
		free_cmd_list(cmd->next);
	if (cmd->command)
	{
		free(cmd->command);
		cmd->command = NULL;
	}
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
			i++;
		}
		free(cmd->args);
		cmd->args = NULL;
	}
	free(cmd);
	cmd = NULL;
}



int	main(int c, char **v, char **env)
{
	t_lex	*lex;
	char	*input;
	t_cmd	*cmd;

	lex = NULL;
	(void)c;
	(void)v;
	(void)env;
	while (1)
	{
		input = readline("minishell$>");
		if (ft_strlen(input) > 0)
		{
			input[ft_strlen(input)] = '\0';
			add_history(input);
			input = expand_var(input, env);
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
					free_list(&lex);
					puts("before command");
					if (cmd)
					{
						free_cmd_list(cmd);
					}
					puts("after command");
				}
			}
		}
		free(input);
		input = NULL;
	}
	return (0);
}
