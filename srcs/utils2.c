/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:33:40 by jacens            #+#    #+#             */
/*   Updated: 2020/02/17 18:51:07 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**ft_lst_to_char(t_list *env)
{
	char	**envp;
	int		i;

	i = ft_lstsize(env);
	if (!(envp = malloc((i + 1) * sizeof(char*))))
		return (NULL);
	i = 0;
	while (env)
	{
		if (((t_tag *)(env->content))->tag)
		{
			if (!(envp[i] = ft_strdup(((t_tag *)(env->content))->str)))
				return (0);
			if (!(envp[i] = ft_append(envp[i], "=", 1)))
				return (0);
			if (!(envp[i] = ft_append(envp[i], ((t_tag *)(env->content))->value,
			ft_strlen(((t_tag *)(env->content))->value))))
				return (0);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int			check_line(t_list *list)
{
	if (list)
		list = list->next;
	while (list && (((t_tag *)(list->content))->tag >= 0 ||
	((t_tag *)(list->content))->tag == -32))
	{
		if (check_setvar(list, 0, 0) || ((t_tag *)(list->content))->tag == -32)
			list = list->next;
		else
			break ;
	}
	if (list && ((t_tag *)(list->content))->tag >= 0)
		return (1);
	return (0);
}

char		**ft_sortup(char **lst)
{
	char	*tmp;
	int		i;
	int		size;

	size = 0;
	while (lst[size])
		size++;
	size--;
	while (size > 0)
	{
		i = 0;
		while (i < size)
		{
			if (ft_strcmp(lst[i], lst[i + 1]) > 0)
			{
				tmp = lst[i];
				lst[i] = lst[i + 1];
				lst[i + 1] = tmp;
			}
			i++;
		}
		size--;
	}
	return (lst);
}

int			ft_free_foo(char **foo, int j)
{
	int i;

	i = -1;
	if (j == 1)
	{
		if (foo[0])
		{
			free(foo[0]);
			foo[0] = NULL;
		}
	}
	else
		while (foo[++i])
		{
			free(foo[i]);
			foo[i] = NULL;
		}
	free(foo);
	foo = NULL;
	return (0);
}

void		ft_signal(int i)
{
	if (i == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (i == 1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (i == 2)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigint);
	}
}
