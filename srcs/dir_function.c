/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 06:29:53 by jacens            #+#    #+#             */
/*   Updated: 2020/02/21 04:29:10 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	chdir_do_one_dir2(t_list *command_list, t_list *env, char *cp)
{
	int		nb;
	int		i;
	char	*tmp;

	tmp = cp;
	while (((t_tag *)(env->content)) &&
	(ft_strcmp(&((t_tag *)(command_list->content))->str[1],
	((t_tag *)(env->content))->str)) != 0)
		env = env->next;
	if (((t_tag *)(env->content)))
	{
		nb = ft_strcount_char(&cp[1], 47);
		ft_strcmp(cp, "/") != 0 ? nb++ : 0;
		cp = ((t_tag *)(env->content))->value;
		i = ft_strcount_char(&cp[1], 47);
		while (--nb > -1)
			chdir("..");
		cp = ((t_tag *)(env->content))->value;
		chdir(&cp[0]) == -1 ? ft_err_chdir(1, cp, env, tmp) :
		ft_lst_env_pwd(env, &tmp[0]);
	}
}

static void	chdir_do_one_dir(t_list *command_list, t_list *env, char *cp)
{
	int		ret;

	if (!ft_strncmp(((t_tag *)(command_list->content))->str, "~", 1) &&
	((t_tag *)(command_list->content))->tag != 39)
		chdir_home_cmd(command_list, env, cp, cp);
	else if (!ft_strncmp(((t_tag *)(command_list->content))->str, "$", 1)
	&& ((t_tag *)(env->content))->tag != 39)
		chdir_do_one_dir2(command_list, env, cp);
	else
	{
		ret = chdir(((t_tag *)(command_list->content))->str);
		(ret == -1) ? ft_err_chdir(0, ((t_tag *)(command_list->content))->str,
		env, NULL) :
		ft_lst_env_pwd(env, cp);
	}
}

static void	chdir_verif_one_dir(t_list *command_list, t_list *env, char *cp)
{
	if (!command_list->next)
		chdir_do_one_dir(command_list, env, cp);
	else if (((t_tag *)(command_list->next->content))->tag == -59 ||
	((t_tag *)(command_list->next->content))->tag == -124)
		chdir_do_one_dir(command_list, env, cp);
	else if (!command_list->next->next)
		chdir_do_one_dir(command_list, env, cp);
	else if (((t_tag *)(command_list->next->next->content))->tag == -32 &&
		!command_list->next->next->next)
		chdir_do_one_dir(command_list, env, cp);
	else if (((t_tag *)(command_list->next->next->content))->tag < 0)
		chdir_do_one_dir(command_list, env, cp);
	else
	{
		ft_printf_fd(2, "cd: to many arguments\n");
		fill_ret_env(env, 1);
	}
}

int			cd_command(t_list *command_list, t_list *env)
{
	char	*cp;

	if (!(cp = ft_get_pwd()) || fill_ret_env(env, 0))
		return (1);
	if (!command_list)
		chdir_home_cmd(command_list, env, cp, cp);
	else
	{
		if (((t_tag *)(command_list->content))->tag == -59 ||
		((t_tag *)(command_list->content))->tag == -124)
			chdir_home_cmd(command_list, env, cp, cp);
		else
		{
			command_list = skip_redir_go_next(command_list);
			if (!command_list)
				chdir_home_cmd(command_list, env, cp, cp);
			else if (((t_tag *)(command_list->content))->tag == -59 ||
			((t_tag *)(command_list->content))->tag == -124)
				chdir_home_cmd(command_list, env, cp, cp);
			else
				chdir_verif_one_dir(command_list, env, cp);
		}
	}
	free(cp);
	return (0);
}
