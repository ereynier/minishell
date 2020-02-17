/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_function_more.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:28:59 by jacens            #+#    #+#             */
/*   Updated: 2020/02/17 11:26:27 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	reset_dir_or_set_env(t_list *env, t_list *command_list, char *tmp,
								int i)
{
	char *cp;

	cp = ((t_tag *)(command_list->content))->str;
	if (chdir(&cp[2]) != -1)
		return (1);
	while (--i > -1)
		chdir("..");
	ft_err_chdir(1, cp, env, tmp);
	return (0);
}

void		chdir_home_cmd(t_list *command_list, t_list *env,
						char *cp, char *tmp)
{
	int		nb;
	int		i;

	while (((t_tag *)(env->content)) &&
	ft_strncmp(((t_tag *)(env->content))->str, "HOME", 5) != 0)
		env = env->next;
	if (env && ((t_tag *)(env->content))->tag == 1)
	{
		nb = ft_strcount_char(&cp[1], 47);
		ft_strcmp(cp, "/") != 0 ? nb++ : 0;
		cp = ((t_tag *)(env->content))->value;
		i = nb;
		while (--nb > -1)
			chdir("..");
		(chdir(&cp[0]) == -1) ? ft_err_chdir(1, cp, env, tmp) :
		ft_lst_env_pwd(env, &tmp[0]);
		if (command_list &&
		ft_strncmp(((t_tag *)(command_list->content))->str, "~", 1) == 0
		&& ft_strlen(((t_tag *)(command_list->content))->str) != 1)
			if (reset_dir_or_set_env(env, command_list, tmp, i) == 1)
				ft_lst_env_pwd(env, &tmp[0]);
	}
}

int			ft_lst_env_pwd(t_list *lst, char *old)
{
	t_list	*tmp;

	tmp = lst;
	while (((t_tag *)(tmp->content)) &&
	ft_strncmp(((t_tag *)(tmp->content))->str, "OLDPWD", 7) != 0)
		tmp = tmp->next;
	if (((t_tag *)(tmp->content)) && old)
	{
		free(((t_tag *)(tmp->content))->value);
		if (!(((t_tag *)(tmp->content))->value = ft_strdup(old)))
			return (0);
	}
	tmp = lst;
	while (((t_tag *)(tmp->content)) &&
	ft_strncmp(((t_tag *)(tmp->content))->str, "PWD", 4) != 0)
		tmp = tmp->next;
	if (((t_tag *)(tmp->content)))
	{
		free(((t_tag *)(tmp->content))->value);
		if (!(((t_tag *)(tmp->content))->value = ft_get_pwd()))
			return (0);
	}
	return (1);
}

int			ft_err_chdir(int i, char *str, t_list *env, char *tmp)
{
	i == 1 ? chdir(&tmp[1]) : 0;
	ft_printf_fd(2,
	"\033[1;31mminishell\033[0m: no such file or directory: %s\n",
	str) == -1 ? i = -1 : 0;
	if (fill_ret_env(env, 1) || i == -1)
		return (1);
	return (0);
}
