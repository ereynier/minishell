/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 17:33:05 by jacens            #+#    #+#             */
/*   Updated: 2020/02/17 13:58:59 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_change_dup_write(t_list *lst)
{
	int		file;
	int		stdout_bkp;

	while (lst && ((t_tag *)(lst->content))->tag != -62 &&
		((t_tag *)(lst->content))->tag != -63 &&
		((t_tag *)(lst->content))->tag != -59 &&
		((t_tag *)(lst->content))->tag != -124)
		lst = lst->next;
	if (!lst || (((t_tag *)(lst->content))->tag != -62 &&
		((t_tag *)(lst->content))->tag != -63))
		return (-1);
	file = open(((t_tag *)(lst->next->content))->str, O_CREAT | O_WRONLY |
		O_APPEND, 0644);
	stdout_bkp = dup(STDOUT_FILENO);
	dup2(file, STDOUT_FILENO);
	close(file);
	return (stdout_bkp);
}

int			ft_change_dup_read(t_list *lst)
{
	int		file;
	int		stdin_bkp;

	while (lst && ((t_tag *)(lst->content))->tag != -60 &&
	((t_tag *)(lst->content))->tag != -59 &&
	((t_tag *)(lst->content))->tag != -124)
		lst = lst->next;
	if (!lst || (((t_tag *)(lst->content))->tag != -60))
		return (-1);
	file = open(((t_tag *)(lst->next->content))->str, O_RDONLY,
	0644);
	stdin_bkp = dup(STDIN_FILENO);
	dup2(file, STDIN_FILENO);
	close(file);
	return (stdin_bkp);
}

void		ft_reset_redir(int in, int out)
{
	if (in != -1)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != -1)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

void		ft_remove_start_dir(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while ((((t_tag *)(tmp->content))->tag == -62 ||
	((t_tag *)(tmp->content))->tag == -63 ||
	((t_tag *)(tmp->content))->tag == -60) &&
	(tmp->next && tmp->next->next && tmp->next->next->next))
		tmp = tmp->next->next->next;
	*lst = tmp;
}

void		ft_change_order_more(t_list *sp, t_list *redir,
			t_list *redirsp, t_list *file)
{
	t_list	*avlast;

	redir = sp->next;
	file = redir->next;
	redirsp = (file->next ? file->next : NULL);
	if (redirsp)
	{
		avlast = redirsp;
		while (avlast->next && ((t_tag *)(avlast->next->content))->tag
		!= -59 && ((t_tag *)(avlast->next->content))->tag != -124)
			avlast = avlast->next;
		avlast == redirsp ? avlast = NULL : 0;
		if (avlast)
		{
			sp->next = redirsp->next;
			file->next = avlast->next;
			avlast->next = redirsp;
			redirsp->next = redir;
		}
	}
}
