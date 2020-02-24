/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:45:52 by jacens            #+#    #+#             */
/*   Updated: 2020/02/21 00:12:07 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_free_split_ret(char **split, int i)
{
	while (split[++i])
		free(split[i]);
	free(split);
	return (NULL);
}

static char	*ft_config_cmd_path(char **split, char *cmd, char *ret)
{
	int			i;
	char		*tmp;
	struct stat	sb;

	i = -1;
	if (!cmd)
	{
		ft_free_foo(split, 2);
		return (ft_strdup(ret));
	}
	while (split[++i])
	{
		split[i] = ft_strjoin(split[i], cmd);
		if (split[i] == NULL)
			return (ft_free_split_ret(split, i));
		if (stat(split[i], &sb) != -1)
		{
			tmp = split[i];
			ft_free_split_ret(split, i);
			return (tmp);
		}
	}
	return (ft_strdup(ret));
}

static char	*ft_cmd_path_check(char *path, char *cmd)
{
	char		*tmp;
	char		**split;
	struct stat	sb;

	tmp = NULL;
	split = NULL;
	if (!path)
		return (cmd);
	if (!(split = ft_split(path, ':')))
		return (NULL);
	if (stat(cmd, &sb) == -1)
		return (ft_config_cmd_path(split, ft_strjoin("/", cmd), cmd));
	return (ft_strdup(cmd));
}

static int	set_value_env(int status, t_list *env)
{
	if (fill_ret_env(env, 0))
		return (1);
	if (status == 2)
		if (fill_ret_env(env, 130))
			return (1);
	if (status == 3)
		if (fill_ret_env(env, 131))
			return (1);
	if (status == 65280)
		if (fill_ret_env(env, 127))
			return (1);
	if (status == 256)
		if (fill_ret_env(env, 1))
			return (1);
	return (0);
}

int			execve_command(t_list *command_list, t_list *env, char *cmd)
{
	char	*tmp;
	pid_t	pid;
	int		status;
	t_list	*lst;

	ft_signal(0);
	pid = fork();
	if (pid == 0)
	{
		ft_signal(1);
		lst = env;
		while (((t_tag *)(lst->content)) &&
		ft_strncmp(((t_tag *)(lst->content))->str, "PATH", 5) != 0)
			lst = lst->next;
		if (!(tmp = ft_cmd_path_check(((t_tag *)(lst->content))->value, cmd)))
			exit(-1);
		if (!(config_foo(tmp, command_list, env)))
			exit(-1);
		exit(0);
	}
	wait(&status);
	if (set_value_env(status, env))
		return (1);
	ft_signal(2);
	return (0);
}
