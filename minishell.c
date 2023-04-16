/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:40:33 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/16 16:05:25 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex	*lexer(char *input)
{
	t_data	h;
	t_lex	*lex;

	h.i = -1;
	lex = NULL;
	h.s = NULL;
	while (input[++h.i])
	{
		if (input[(h.i)] == '\'' || input[h.i] == '\"')
			dqoute_handler(input, &h, &lex);
		else
		{
			while (input[h.i] == ' ' || input[h.i] == '\t')
				h.i++;
			while (input[h.i] != ' ' && input[h.i] != '\t' && input[h.i])
				h.s = ft_strjoin_characters(h.s, input[h.i++]);
			ft_lstadd_back_lexer(&lex, new_lex(h.s, WORD));
		}
		free(h.s);
		h.s = NULL;
		if (!input[h.i])
			break ;
	}
	return (lex);
}

void	assign_type(t_lex *p)
{
	int		i;
	t_lex	*tmp;

	tmp = p;
	i = 0;
	while (p)
	{
		if (!ft_strcmp(">", p->str))
			p->type = REDIRECT;
		else if (!ft_strcmp(">>", p->str))
			p->type = APPEND;
		else if (!ft_strcmp("<", p->str))
		{
			p->prev->type = IN_FILE;
			p->type = READ_INPUT;
		}
		else if (!ft_strcmp("<<", p->str))
			p->type = HEREDOC;
		else
			check_rest_type(p, &i);
		p = p->next;
	}
	p = tmp;
}

char	*insert_spaces(char *input)
{
	int		i;
	char	*ret;
	char	character;

	i = -1;
	ret = NULL;
	while (input[++i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
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
	return (ret);
}

t_env	*get_env(char **env)
{
	int		s;
	t_data	h;
	t_env	*envp;

	h.i = 0;
	s = 0;
	envp = NULL;
	while (env[h.i])
	{
		h.j = 0;
		s = 0;
		while (env[h.i][h.j])
		{
			while ((env[h.i][h.j] == ' '
				|| env[h.i][h.j] == '\t') && env[h.i][h.j])
				h.j++;
			if (env[h.i][h.j] == '=' && s == 0)
			{
				h.arr[0] = ft_substr(env[h.i], s, h.j);
				s = h.j + 1;
			}
			else if (s)
			{
				h.arr[1] = ft_strdup(&env[h.i][s]);
				ft_lstadd_back_env(&envp, lst_new_env(h.arr[0], h.arr[1]));
				break ;
			}
			h.j++;
		}
		h.i++;
	}
	return (envp);
}

void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

t_exp	*get_exp(char **env)
{
	t_exp	*exp;
	t_exp	*tmp;
	int		i;

	exp = NULL;
	i = 0;
	tmp = exp;
	while (env[i])
	{
		ft_lstadd_back_exp(&exp, lst_new_exp(env[i]));
		i++;
	}
			// printf("here");
	// while (exp)
	// {
	// 	if (ft_strcmp(exp->s, exp->next->name))
	// 	{
	// 		ft_swap(&exp->s, &exp->next->s);
	// 	}
	// 	exp = exp->next;
	// }
	// exp = tmp;
	return (exp);
}

void	sort_env_for_export(t_exp **exp)
{
	t_exp	*tmp;
	t_exp	*tmp2;
	int		i;

	i = 0;
	tmp = *exp;
	tmp2 = *exp;
	while (tmp)
	{
		while (tmp2)
		{
			if (tmp2->next)
				if (ft_strcmp(tmp->s, tmp2->s) < 0)
					ft_swap(&tmp->s, &tmp2->s);
			tmp2 = tmp2->next;
		}
		tmp2 = *exp;
		tmp = tmp->next;
	}
}

int	main(int c, char **v, char **env)
{
	t_exp	*exp;
	t_env	*anv;

	(void)c;
	(void)v;
	anv = get_env(env);
	exp = get_exp(env);
	sort_env_for_export(&exp);
	while (exp)
	{
		printf("%s\n", exp->s);
		exp = exp->next;
	}
	return (0);
}


// whats next is to get the final linked list ready for it is important to organize the input in order to make it easier to execute it