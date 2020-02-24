/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande_cmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 20:15:47 by jacens            #+#    #+#             */
/*   Updated: 2020/02/24 12:40:32 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	command_cmp_do(t_list *list, t_list **command_list, t_list **env,
			char *com)
{
	int		ret;

	ret = 1;
	list ? list = skip_redir_to_go_next(list) : 0;
	if ((!list && !com) || (!ft_strncmp(com, ">", 2) ||
	!ft_strncmp(com, "<", 2) || !ft_strncmp(com, ">>", 3)))
		ret = 0;
	else if (!ft_strncmp(com, "cd", 3))
		ret = cd_command(list, *env);
	else if (!ft_strncmp(com, "env", 4))
		ret = env_command(list, *env);
	else if (!ft_strncmp(com, "echo", 5))
		ret = echo_command(list, 1, *env);
	else if (!ft_strncmp(com, "pwd", 4))
		ret = pwd_command(list);
	else if (!ft_strncmp(com, "export", 7))
		ret = export_command(list, *env);
	else if (!ft_strncmp(com, "unset", 6))
		ret = unset_command(list, *env);
	else if (!ft_strncmp(com, "exit", 5))
		exit_command(list, command_list, env, 0);
	else
		ret = execve_command(list, *env, com);
	return (ret);
}

static int	do_fork_pipe(t_list *list, t_list **command_list, t_list **env,
		char *com)
{
	pid_t	pid;
	int		status;
	int		fd[4];

	pipe(fd);
	fd[3] = dup(STDIN_FILENO);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_change_dup_read(list);
		ft_change_dup_write(list);
		close(fd[1]);
		command_cmp_do(list, command_list, env, com);
		exit(0);
	}
	wait(&status);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	fd[2] = next_command_pipe(list, command_list, env, com);
	dup2(fd[3], STDIN_FILENO);
	close(fd[3]);
	return (fd[2]);
}

int			command_cmp(t_list *list, t_list **command_list, t_list **env,
		char *com)
{
	int		pipe;
	t_list	*tmp;
	int		in;
	int		out;

	pipe = 0;
	tmp = *command_list;
	while (tmp && ((t_tag *)(tmp->content))->tag != -59)
	{
		if (((t_tag *)(tmp->content))->tag == -124)
			pipe = 1;
		tmp = tmp->next;
	}
	if (pipe == 1)
		pipe = do_fork_pipe(list, command_list, env, com);
	else
	{
		in = ft_change_dup_read(list);
		out = ft_change_dup_write(list);
		pipe = command_cmp_do(list, command_list, env, com);
		ft_reset_redir(in, out);
	}
	return (pipe);
}

int			next_command_pipe(t_list *list, t_list **command_list, t_list **env,
		char *com)
{
	t_list	*copy;
	t_list	*tmp;
	int		ret;

	ret = -1;
	tmp = *command_list;
	while (tmp && ((t_tag *)(tmp->content))->tag != -59 &&
			((t_tag *)(tmp->content))->tag != -124)
		tmp = skip_redir_go_next(tmp);
	if (tmp && ((t_tag *)(tmp->content))->tag == -124)
	{
		copy = tmp->next;
		tmp = skip_redir_go_next(tmp);
		com = ((t_tag *)(tmp->content))->str;
		while (com[++ret])
			com[ret] = ft_tolower(com[ret]);
		list = tmp;
		ret = ft_verif_redir(list, &copy, env, com);
	}
	return (ret);
}
