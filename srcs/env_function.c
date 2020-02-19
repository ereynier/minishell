/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 06:29:53 by jacens            #+#    #+#             */
/*   Updated: 2020/02/17 18:50:56 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_list	*ft_unset(char *str, t_list *env)
{
	t_list	*tmp;
	t_list	*pre;

	tmp = env;
	pre = env;
	while (tmp)
	{
		if (!ft_strcmp(((t_tag *)(tmp->content))->str, str))
		{
			if (env == tmp)
				env = env->next;
			else
				pre->next = tmp->next;
			ft_lstdelone(tmp, free);
			break ;
		}
		pre = tmp;
		tmp = tmp->next;
	}
	return (env);
}

int				unset_command(t_list *command_list, t_list *env)
{
	char	*str;
	int		i;

	i = 0;
	while (1)
	{
		if (!(str = malloc(1)))
			return (1);
		str[0] = 0;
		while (command_list && (((t_tag *)(command_list->content))->tag == -32))
			command_list = command_list->next;
		if (!command_list || ((t_tag *)(command_list->content))->tag < 0)
			break ;
		if (check_setvar(command_list, 2, 0))
		{
			str = append_line(&command_list, env);
			env = ft_unset(str, env);
		}
		else
			fill_ret_env(env, 1);
		free(str);
		command_list = command_list ? command_list->next : command_list;
	}
	free(str);
	return (0);
}

int				export_command(t_list *list, t_list *env)
{
	int ret;

	ret = 1;
	if (!list || (list && !list->next) ||
		(list && list->next && ((t_tag *)(list->next->content))->tag < 0))
		print_export(env);
	else
	{
		list = list->next;
		while (list && ((t_tag *)(list->content))->tag >= 0)
		{
			if ((ret = check_env(list, env)) || (check_setvar(list, 1, 0)))
			{
				if (ret != 2)
					preset_var(list, env, 1);
			}
			fill_ret_env(env, 1);
			list = list->next;
			if (list && ((t_tag *)(list->content))->tag == -32)
				list = list->next;
		}
	}
	return (0);
}

static int		get_var(t_list *list, t_list *env)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = malloc(1)))
		return (0);
	str[0] = 0;
	while (((t_tag *)(list->content))->str[i] &&
		((t_tag *)(list->content))->str[i] != '=')
		i++;
	str = ft_append(str, ((t_tag *)(list->content))->str, i);
	i++;
	while (env && ft_strcmp(((t_tag *)(env->content))->str, str))
		env = env->next;
	if (env)
	{
		free(((t_tag *)(env->content))->value);
		((t_tag *)(env->content))->value =
			ft_strdup(&((t_tag *)(list->content))->str[i]);
		free(str);
		return (1);
	}
	else
		free(str);
	return (2);
}

int				preset_var(t_list *list, t_list *env, int set)
{
	int		i;
	t_tag	*new;
	char	*str;
	int		ret;

	if (!(ret = get_var(list, env)))
		return (1);
	if (ret == 2)
	{
		i = 0;
		if (!(new = malloc(sizeof(t_tag))))
			return (1);
		if (!(str = malloc(1)))
			return (1);
		str[0] = 0;
		while (((t_tag *)(list->content))->str[i] != '=')
			i++;
		str = ft_append(str, ((t_tag *)(list->content))->str, i);
		i++;
		new->value = ft_strdup(&((t_tag *)(list->content))->str[i]);
		new->str = str;
		new->tag = set;
		ft_lstadd_back(&env, ft_lstnew(new));
	}
	return (0);
}
