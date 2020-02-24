/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:47:23 by jacens            #+#    #+#             */
/*   Updated: 2020/02/21 00:10:11 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		echo_line(t_list *list, int fd, int i, char *path)
{
	while (i > 0)
	{
		if (list && (((t_tag *)(list->content))->tag >= 0 ||
		((t_tag *)(list->content))->tag == -32))
		{
			i == 2 ? ft_printf_fd(fd, " ") : 0;
			ft_strcmp(((t_tag *)(list->content))->str, "~") == 0 &&
			((t_tag *)(list->content))->tag == 0 ? ft_printf_fd(fd, "%s", path)
			: ft_printf_fd(fd, "%s", ((t_tag *)(list->content))->str);
		}
		else
			i = 0;
		if (i > 0)
		{
			i = 2;
			list->next ? list = list->next : 0;
			if (((t_tag *)(list->content)) &&
			((t_tag *)(list->content))->tag == -32)
				list = skip_redir_go_next(list);
			else
				i = 0;
		}
	}
	return (i);
}

static t_list	*echo_command2(t_list *list, int n)
{
	while (n == 1)
	{
		if (((t_tag *)(list->content)) &&
		strcmp(((t_tag *)(list->content))->str, "-n") == 0)
		{
			if (list->next)
				list = list->next;
			else
				n = 2;
		}
		if (((t_tag *)(list->content)))
		{
			if (((t_tag *)(list->content))->tag == -32 &&
			list->next)
				list = skip_redir_go_next(list);
			else
				n = 2;
		}
		else
			n = 2;
	}
	return (list);
}

int				echo_command(t_list *command_list, int fd, t_list *env)
{
	int		n;
	char	*cp;
	int		i;

	n = 0;
	i = 0;
	while (((t_tag *)(env->content)) &&
	ft_strncmp(((t_tag *)(env->content))->str, "HOME", 5) != 0)
		env = env->next;
	cp = ((t_tag *)(env->content)) ? ((t_tag *)(env->content))->str : NULL;
	if (command_list && command_list->next)
	{
		command_list = skip_redir_go_next(command_list);
		if (strcmp(((t_tag *)(command_list->content))->str, "-n") == 0)
			n = 1;
		command_list = echo_command2(command_list, n);
		if (((t_tag *)(command_list->content)) &&
		strcmp(((t_tag *)(command_list->content))->str, "-n") != 0)
			i = echo_line(command_list, fd, 1, cp);
	}
	n == 0 ? ft_printf("\n") : 0;
	i *= -1;
	if (fill_ret_env(env, 0))
		return (1);
	return (i);
}
