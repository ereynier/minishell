/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:17:22 by jacens            #+#    #+#             */
/*   Updated: 2020/02/17 19:54:11 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			pwd_command(t_list *command_list)
{
	char	*buf;

	if (!(buf = ft_get_pwd()))
		return (1);
	ft_printf("%s\n", buf);
	free(buf);
	(void)command_list;
	return (0);
}

int			env_command(t_list *command_list, t_list *env)
{
	if (command_list)
	{
		if (((t_tag *)(command_list->content))->tag >= 0)
		{
			ft_printf_fd(2, "env: too many arguments\n");
			return (1);
		}
		if (((t_tag *)(command_list->content))->tag == -32 &&
		command_list->next)
			if (((t_tag *)(command_list->next->content))->tag >= 0)
			{
				ft_printf_fd(2, "env: too many arguments\n");
				return (1);
			}
	}
	while (env)
	{
		if (((t_tag *)(env->content))->tag)
			ft_printf("%s=%s\n", ((t_tag *)(env->content))->str,
			((t_tag *)(env->content))->value);
		env = env->next;
	}
	return (0);
}

static void	set_lower_case(t_list *list, int i)
{
	while (list)
	{
		i = 0;
		if (list && (((t_tag *)(list->content))->tag < 0 ||
			!check_setvar(list, 0, 0)))
		{
			while (((t_tag *)(list->content))->str[i])
			{
				((t_tag *)(list->content))->str[i] =
					ft_tolower(((t_tag *)(list->content))->str[i]);
				i++;
			}
			while (list && ((t_tag *)(list->content))->tag != -59 &&
				((t_tag *)(list->content))->tag != -124)
				list = list->next;
			if (list)
				list = list->next;
		}
		else
		{
			((t_tag *)(list->content))->tag = -61;
			list = list->next;
		}
	}
}

int			call_command(t_list **command_list, t_list **env)
{
	char	*com;
	t_list	*list;

	list = *command_list;
	com = 0;
	while (1)
	{
		while (list && (((t_tag *)(list->content))->tag == -32
		|| ((t_tag *)(list->content))->tag == -59))
			list = list->next;
		if (!list)
			return (0);
		if (com == NULL)
		{
			reconfig_command(command_list, *env);
			set_lower_case(list, 0);
		}
		if (call_command_norme(&list, &command_list, &env, &com))
			return (1);
	}
}
