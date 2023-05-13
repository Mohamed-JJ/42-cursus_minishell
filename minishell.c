/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/13 12:53:26 by mjarboua         ###   ########.fr       */
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

void	f(void)
{
	system("leaks minishell");
}

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

// t_cmd	*create_cmd(t_lex *s)
// {
// 	t_cmd	*ret;
// 	t_data	d;

// 	ret = NULL;
// 	d.arr = NULL;
// 	while (s)
// 	{
// 		if (!d.arr)
// 			d.arr = empty_array();
// 		if (s->type == COMMAND)
// 			d.s = ft_strdup(s->str);
// 		else if (s->type == ARGUMENT)
// 			d.arr[0] = join_string(s->str, &d.arr[0]);
// 		else if (s->type == OUT_FILE)
// 			d.arr[1] = join_string(s->str, &d.arr[1]);
// 		else if (s->type == IN_FILE)
// 			d.arr[2] = join_string(s->str, &d.arr[2]);
// 		else if (s->type == HEREDOC_DEL)
// 			d.arr[3] = join_string(s->str, &d.arr[3]);
// 		if (s->type == PIPE || !s->next)
// 		{
// 			ft_lstadd_back_cmd(&ret, new_command(&d));
// 			if (d.s)
// 				free_string(&d.s);
// 			if (d.arr)
// 			{
// 				for (int i = 0; i < 4; i++)
// 					free_string(&d.arr[i]);
// 				free(d.arr);
// 				d.arr = NULL;
// 			}
// 		}
// 		s = s->next;
// 		}
// 	return (ret);
// }

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
	return (new_command(*str, arr, i));
}

t_cmd	*create_cmd(t_lex *s)
{
	char	**arr;
	char	*str;
	t_cmd	*ret;

	ret = NULL;
	arr = NULL;
	str = ft_strdup("");
	while (s)
	{
		arr = empty_array();
		ft_lstadd_back_cmd(&ret, fill_till_eol_pipe(&str, arr, &s));
		if (s && s->type == PIPE)
			puts("pipe");
		puts("here");
		printf("the command %s\n", str);
		printf("the args %s\n", arr[0]);
		printf("the outfile %s\n", arr[1]);
		
		if (str)
			free_string(&str);
		puts("before freeing arrary");
		if (arr)
		{
			for (int i = 0; i < 4; i++)
			{
				free(arr[i]);
				arr[i] = NULL;
			}
			free(arr);
			arr = NULL;
		}
		if (s == NULL)
		{
			puts("next is NULL");
			break ;
		}
		exit(0);
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

void	free_list(void	**list, int flag)
{
	t_lex	*tmp;
	t_cmd	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (flag)
	{
		tmp = (t_lex *)*list;
		while (tmp)
		{
			free(tmp->str);
			free(tmp);
			tmp = tmp->next;
		}
		free(tmp);
		tmp = NULL;
	}
	else
	{
		tmp2 = (t_cmd *)*list;
		while (tmp2)
		{
			if (tmp2->command)
				free_string(&tmp2->command);
			free_array(tmp2->args);
			free_array(tmp2->outfile);
			free_array(tmp2->infile);
			free_array(tmp2->heredoc_del);
			tmp2 = tmp2->next;
		}
		free(tmp2);
		tmp2 = NULL;
	}
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
		cmd = NULL;
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
					free_list((void **)&lex, 1);
				else
				{
					cmd = create_cmd(lex);
					free_list((void **)&lex, 1);
					puts("before command");
					if (cmd)
					{
					while (cmd)
					{
						if (cmd->command)
						{
							free(cmd->command);
							cmd->command = NULL;
						}
						
						int i = 0;
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
						if (cmd->outfile)
						{
						while (cmd->outfile[i])
						{
							free(cmd->outfile[i]);
							cmd->outfile[i] = NULL;
							i++;
						}
						free(cmd->outfile);
						cmd->outfile = NULL;
						}
						i = 0;
						t_cmd *next_cmd = cmd->next;
						free(cmd);
						cmd = next_cmd;
					}
					cmd = NULL;
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
