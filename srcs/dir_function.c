/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dir_function.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/11 06:29:53 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 16:02:02 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	chdir_home_cmd(t_list *command_list, t_list *env,
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
		i = ft_strcount_char(&cp[1], 47);
		while (--nb > -1)
			chdir("..");
		if (chdir(&cp[0]) == -1)
			chdir(&tmp[1]);
		if (command_list &&
		ft_strncmp(((t_tag *)(command_list->content))->str, "~", 1) == 0
		&& ft_strlen(((t_tag *)(command_list->content))->str) != 1)
		{
			cp = ((t_tag *)(command_list->content))->str;
			if (chdir(&cp[2]) == -1)
				chdir(&tmp[1]);
		}
	}
}

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
		if (chdir(&cp[1]) == -1)
			chdir(&tmp[1]);
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
		ret == -1 ? ft_printf("minishell: no such file or directory: %s\n",
		((t_tag *)(command_list->content))->str) : 0;
	}
}

static void	chdir_verif_one_dir(t_list *command_list, t_list *env, char *cp)
{
	if (!command_list->next)
		chdir_do_one_dir(command_list, env, cp);
	else if (((t_tag *)(command_list->next->content))->tag == -59)
		chdir_do_one_dir(command_list, env, cp);
	else if (!command_list->next->next)
		chdir_do_one_dir(command_list, env, cp);
	else if (((t_tag *)(command_list->next->next->content))->tag == -32 &&
		!command_list->next->next->next)
		chdir_do_one_dir(command_list, env, cp);
	else if (((t_tag *)(command_list->next->next->content))->tag == -59)
		chdir_do_one_dir(command_list, env, cp);
	else
		ft_printf("cd: to many arguments\n");
}

int			cd_command(t_list *command_list, t_list *env)
{
	char	*cp;

	if (!(cp = ft_get_pwd()))
		return (1);
	if (!command_list)
		chdir_home_cmd(command_list, env, cp, cp);
	else
	{
		if (((t_tag *)(command_list->content))->tag == -59)
			chdir_home_cmd(command_list, env, cp, cp);
		else
		{
			command_list = command_list->next;
			if (!command_list)
				chdir_home_cmd(command_list, env, cp, cp);
			else if (((t_tag *)(command_list->content))->tag == -59)
				chdir_home_cmd(command_list, env, cp, cp);
			else
				chdir_verif_one_dir(command_list, env, cp);
		}
	}
	free(cp);
	return (0);
}
