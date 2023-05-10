/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/05/10 22:19:53 by mjarboua         ###   ########.fr       */
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

t_cmd	*new_command(t_data *p)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd ));
	if (!ret)
		return (NULL);
	ret->command = ft_strdup(p->s);
	fill_arrays(p->arr[0], &ret->args);
	fill_arrays(p->arr[1], &ret->outfile);
	fill_arrays(p->arr[2], &ret->infile);
	fill_arrays(p->arr[3], &ret->heredoc_del);
	ret->in_out = p->i;
	return (ret);
}

void ft_lstadd_back_cmd(t_cmd **c, t_cmd *new)
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



t_cmd	*create_cmd(t_lex *s)
{
	t_cmd	*ret;
	t_data	d;

	d.i = 0;
	ret = NULL;
	while (s)
	{
		d.arr = empty_array();
		redirection_type(s->type, &d);
		if (s->type == COMMAND)
			d.s = ft_strdup(s->str);
		if (s->type == ARGUMENT)
			join_string(s->str, &d.arr[0]);
		else if (s->type == OUT_FILE)
			join_string(s->str, &d.arr[1]);
		else if (s->type == IN_FILE)
			join_string(s->str, &d.arr[2]);
		else if (s->type == HEREDOC_DEL)
			join_string(s->str, &d.arr[3]);
		else if (s->type == PIPE)
		{
			t_cmd *tmp = new_command(&d);
			ft_lstadd_back_cmd(&ret, tmp);
			int i  = 0;
			while (d.arr[i])
			{
				free(d.arr[i]);
				d.arr[i] = NULL;
				i++;
			}
			d.arr = NULL;
		}
		s = s->next;
	}
	ft_lstadd_back_cmd(&ret, new_command(&d));
	return (ret);
}

int	main(int c, char **v, char **env)
{
	t_lex	*lex;
	char	*input;
	// t_cmd	*cmd;

	lex = NULL;
	(void)c;
	(void)v;
	(void)env;
	while (1)
	{
		input = readline("minishell$>:");
		if (ft_strlen(input) > 0)
		{
			input[ft_strlen(input)] = '\0';
			add_history(input);
			input = expand_var(input, env);
			input = insert_spaces(input);
			lex = lexer(input);
			assign_type(lex);
			manage_type(lex);
			if (generate_error(lex))
			{
				while (lex)
				{
					free(lex->str);
					free(lex);
					lex = lex->next;
				}
			}
			else
				print_list(lex);
			while (lex)
			{
				free(lex->str);
				free(lex);
				lex = lex->next;
			}
		}
		free(input);
		input = NULL;
	}
	return (0);
}
