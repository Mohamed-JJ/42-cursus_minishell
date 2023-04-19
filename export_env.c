/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:47:29 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/18 14:20:47 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_env	*lst_new_env(char *arr, char *name)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = ft_strdup(name);
	new->name = ft_strdup(arr);
	new->next = NULL;
	free(name);
	free(arr);
	arr = NULL;
	name = NULL;
	return (new);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*tmp;

	if (alst && new)
	{
		if (!*alst)
			*alst = new;
		else
		{
			tmp = *alst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

t_exp	*lst_new_exp(char *arr)
{
	t_exp	*new;

	new = malloc(sizeof(t_exp));
	if (!new)
		return (NULL);
	new->s = ft_strdup(arr);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_exp(t_exp **alst, t_exp *new)
{
	t_exp	*tmp;

	if (alst && new)
	{
		if (!*alst)
			*alst = new;
		else
		{
			tmp = *alst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}
