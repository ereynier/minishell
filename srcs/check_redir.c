/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:55:36 by jacens            #+#    #+#             */
/*   Updated: 2020/02/16 12:24:39 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_verif_exist_file(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (-1);
	return (0);
}

static int	ft_open_file_dir(int i, t_list *tmp)
{
	int		fd;

	i = i == 1 ? 2 : 1;
	if (((t_tag *)(tmp->content))->tag == -62)
	{
		fd = open(((t_tag *)(tmp->next->content))->str, O_WRONLY | O_TRUNC |
		O_CREAT, 0644);
	}
	else
		fd = open(((t_tag *)(tmp->next->content))->str, O_CREAT | O_WRONLY |
		O_APPEND, 0644);
	fd < 0 ? i = -1 : 0;
	close(fd);
	return (i);
}

int			ft_check_redir(t_list **command_list)
{
	t_list	*tmp;
	t_list	*backup;
	int		fileopen;

	tmp = *command_list;
	while (tmp)
	{
		backup = tmp;
		fileopen = 0;
		while (tmp && ((t_tag *)(tmp->content))->tag != -59)
		{
			if (fileopen >= 0 && (((t_tag *)(tmp->content))->tag == -62 ||
				((t_tag *)(tmp->content))->tag == -63))
				fileopen = ft_open_file_dir(fileopen, tmp);
			else if (((t_tag *)(tmp->content))->tag == -60)
				if (ft_verif_exist_file(((t_tag *)(tmp->next->content))->str))
					return (1);
			tmp = tmp->next;
		}
		if (fileopen == -1)
			return (1);
		tmp ? tmp = tmp->next : 0;
	}
	return (0);
}
