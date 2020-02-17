/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 16:53:28 by jacens            #+#    #+#             */
/*   Updated: 2020/02/17 16:59:40 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_clear_remove_multi(t_list *lst)
{
	lst->next->next->next = NULL;
	ft_lstclear(&lst, &free);
}

int			ft_remove_all_multi_dir(int i, t_list *tmp, int j)
{
	t_list	*del;
	t_list	*prev;

	while (i > 2)
	{
		while (tmp && tmp->next &&
		((t_tag *)(tmp->next->content))->tag != -62 &&
		((t_tag *)(tmp->next->content))->tag != -63)
			tmp = tmp->next;
		prev = tmp;
		del = prev->next;
		tmp = del->next;
		tmp = tmp->next;
		tmp = tmp->next;
		prev->next = tmp;
		j > 0 ? ft_clear_remove_multi(del) : 0;
		i--;
	}
	return (i);
}

int			ft_remove_all_multi_dirbis(int i, t_list *tmp, int j)
{
	t_list	*del;
	t_list	*prev;

	while (i > 1)
	{
		while (tmp && tmp->next &&
		((t_tag *)(tmp->next->content))->tag != -62 &&
		((t_tag *)(tmp->next->content))->tag != -63)
			tmp = tmp->next;
		prev = tmp;
		del = prev->next;
		tmp = del->next;
		tmp = tmp->next;
		tmp = tmp->next;
		prev->next = tmp;
		j > 0 ? ft_clear_remove_multi(del) : 0;
		i--;
	}
	return (i);
}

int			ft_remove_all_multi_dir2bis(int i, t_list *tmp, int j)
{
	t_list	*del;
	t_list	*prev;

	while (i > 1)
	{
		while (tmp && ((t_tag *)(tmp->next->content))->tag != -60)
			tmp = tmp->next;
		prev = tmp;
		del = prev->next;
		tmp = del->next->next->next;
		prev->next = tmp;
		j > 0 ? ft_clear_remove_multi(del) : 0;
		i--;
	}
	return (i);
}

int			ft_rmv_all_multi_dir2(int i, t_list *tmp, int j)
{
	t_list	*del;
	t_list	*prev;

	while (i > 2)
	{
		while (tmp && ((t_tag *)(tmp->next->content))->tag != -60)
			tmp = tmp->next;
		prev = tmp;
		del = prev->next;
		tmp = del->next->next->next;
		prev->next = tmp;
		j > 0 ? ft_clear_remove_multi(del) : 0;
		i--;
	}
	return (i);
}
