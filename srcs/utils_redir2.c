/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 12:35:57 by jacens            #+#    #+#             */
/*   Updated: 2020/02/17 12:08:11 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_count_nb_redir(t_list *tmp)
{
	int		i;

	i = 0;
	while (tmp && ((t_tag *)(tmp->content))->tag != -59)
	{
		if (((t_tag *)(tmp->content))->tag == -62 ||
			((t_tag *)(tmp->content))->tag == -63)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int			ft_count_nb_redir2(t_list *tmp)
{
	int		i;

	i = 0;
	while (tmp && ((t_tag *)(tmp->content))->tag != -59)
	{
		if (((t_tag *)(tmp->content))->tag == -60)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	ft_change_order_v1(t_list *sp, t_list *redir,
			t_list *redirsp, t_list *file)
{
	while (sp->next && ((t_tag *)(sp->next->content))->tag != -62 &&
	((t_tag *)(sp->next->content))->tag != -63)
		sp = sp->next;
	if (sp->next)
		ft_change_order_more(sp, redir, redirsp, file);
}

static void	ft_change_order_v2(t_list *sp, t_list *redir,
			t_list *redirsp, t_list *file)
{
	while (sp->next && ((t_tag *)(sp->next->content))->tag != -60)
		sp = sp->next;
	if (sp->next)
		ft_change_order_more(sp, redir, redirsp, file);
}

void		ft_change_order_list(t_list *lst)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = lst;
	prev = tmp;
	while (tmp)
	{
		if (ft_count_nb_redir(tmp) > 0)
			ft_change_order_v1(prev, NULL, NULL, NULL);
		if (ft_count_nb_redir2(tmp) > 0)
			ft_change_order_v2(prev, NULL, NULL, NULL);
		prev = tmp;
		while (prev && ((t_tag *)(prev->content))->tag != -59)
			prev = prev->next;
		tmp = prev ? prev->next : NULL;
	}
}
