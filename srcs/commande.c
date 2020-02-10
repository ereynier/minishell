/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   commande.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 13:17:22 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 16:44:46 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			pwd_command(t_list *command_list)
{
	char	*buf;
	int		i;

	i = 5;
	if (command_list)
	{
		if (((t_tag *)(command_list->content))->tag != -32 &&
		((t_tag *)(command_list->content))->tag != -59)
		{
			ft_printf("pwd: too many arguments\n");
			return (1);
		}
		if (((t_tag *)(command_list->content))->tag == -32 &&
		command_list->next)
			if (((t_tag *)(command_list->next->content))->tag != -59)
			{
				ft_printf("pwd: too many arguments\n");
				return (1);
			}
	}
	if (!(buf = ft_get_pwd()))
		return (1);
	ft_printf("%s\n", buf);
	free(buf);
	return (0);
}

int			env_command(t_list *command_list, t_list *env)
{
	if (command_list)
	{
		if (((t_tag *)(command_list->content))->tag >= 0)
		{
			ft_printf("env: too many arguments\n");
			return (1);
		}
		if (((t_tag *)(command_list->content))->tag == -32 &&
		command_list->next)
			if (((t_tag *)(command_list->next->content))->tag >= 0)
			{
				ft_printf("env: too many arguments\n");
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


static int	command_cmp(t_list *command_list, t_list *env, char *com)
{
	int		ret;

	ret = 0;
	if (!ft_strncmp(com, "cd", 3))
		ret = cd_command(command_list, env);
	else if (!ft_strncmp(com, "env", 4))
		ret = env_command(command_list, env);
	else if (!ft_strncmp(com, "echo", 5) ||
	!ft_strncmp(com, "/bin/echo", 10))
		ret = echo_command(command_list, 1, env);
	else if (!ft_strncmp(com, "pwd", 4) ||
	!ft_strncmp(com, "/bin/pwd", 9))
		ret = pwd_command(command_list);
	// else if (!ft_strncmp(com, "export", 7))
	// 	ret = export_command(command_list);
	else if (!ft_strncmp(com, "unset", 6))
		ret = unset_command(command_list, env);
	// else if (!ft_strncmp(com, "exit", 5))
	// 	ret = exit_command(command_list);
	else
		ret = execve_command(command_list, env, com);
	return (ret);
}

static void set_lower_case(t_list *list)
{
	int i;

	while (list)
	{
		i = 0;
		if (list && (((t_tag *)(list->content))->tag < 0 || !check_setvar(list)))
		{
			while (((t_tag *)(list->content))->str[i])
			{
				((t_tag *)(list->content))->str[i] = ft_tolower(((t_tag *)(list->content))->str[i]);
				i++;
			}
			while (list && ((t_tag *)(list->content))->tag != -59 && ((t_tag *)(list->content))->tag != -124)
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

int			call_command(t_list *command_list, t_list *env)
{
	char	*com;

	com = 0;
	while (1)
	{
		while (command_list && (((t_tag *)(command_list->content))->tag == -32
		|| ((t_tag *)(command_list->content))->tag == -59 ))
			command_list = command_list->next;
		if (!command_list)
			return (0);
		if (com == NULL)
		{
			reconfig_command(&command_list, env, 0);
			set_lower_case(command_list);
		}
		t_list *ptr = command_list;//////////////
		while (ptr)////////////////////////
		{///////////////////////////////////////
			printf("\033[0;33m2|->%s, %d\033[0m\n", ((t_tag *)(ptr->content))->str,////////
			((t_tag *)(ptr->content))->tag);///////////// AFFICHE LISTE CHAINEE
			ptr = ptr->next;///////////////////////
		}/////////////////////////////
		if (((t_tag *)(command_list->content))->tag == -61)
		{
			preset_var(command_list, env);
			command_list = command_list->next;
		}
		else
		{
			com = ((t_tag *)(command_list->content))->str;
			command_list = command_list->next;
			if (command_cmp(command_list, env, com))
				return (1);
			while (command_list && ((t_tag *)(command_list->content))->tag != -59
			&& ((t_tag *)(command_list->content))->tag != -61)
				command_list = command_list->next;
		}
	}
}
