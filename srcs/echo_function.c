/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   echo_function.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 17:47:23 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 15:28:28 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		echo_line(t_list *list, int fd, int i, char *path)
{
	char	*print;

	while (i > 0)
	{
		if (((t_tag *)(list->content))->tag != -59)
		{
			i == 2 ? ft_printf_fd(fd, " ") : 0;
			print = ft_strcmp(((t_tag *)(list->content))->str, "~") == 0
			&& ((t_tag *)(list->content))->tag == 0 ?
			path : ((t_tag *)(list->content))->str;
			i = ft_printf_fd(fd, "%s", print);
		}
		else
			i = 0;
		if (i > 0)
		{
			i = 2;
			list->next ? list = list->next : 0;
			if (((t_tag *)(list->content)) &&
			((t_tag *)(list->content))->tag == -32)
				list = list->next;
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
				list = list->next;
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
		command_list = command_list->next;
		if (strcmp(((t_tag *)(command_list->content))->str, "-n") == 0)
			n = 1;
		command_list = echo_command2(command_list, n);
		if (((t_tag *)(command_list->content)) &&
		strcmp(((t_tag *)(command_list->content))->str, "-n") != 0)
			i = echo_line(command_list, fd, 1, cp);
	}
	n == 0 ? ft_printf("\n") : 0;
	i *= -1;
	return (i);
}
