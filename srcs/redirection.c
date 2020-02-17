/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:55:35 by jacens            #+#    #+#             */
/*   Updated: 2020/02/17 18:50:26 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_list		*ft_change_first_caract_more(t_list *carac,
				t_list *tmp, t_list **list)
{
	t_list	*commande;
	t_list	*space;
	t_list	*file;

	file = tmp->next;
	space = file->next;
	commande = space->next;
	file->next = commande->next;
	commande->next = space;
	space->next = carac;
	*list = commande;
	return (commande);
}

static t_list		*ft_change_first_caract(t_list **list)
{
	t_list	*carac;
	t_list	*tmp;

	carac = *list;
	tmp = carac;
	while (tmp->next->next &&
	(((t_tag *)(tmp->next->next->next->content))->tag == -62
	|| ((t_tag *)(tmp->next->next->next->content))->tag == -63 ||
	((t_tag *)(tmp->next->next->next->content))->tag == -60))
	{
		tmp = tmp->next->next->next;
		carac = tmp;
	}
	if (tmp->next->next != NULL)
		return (ft_change_first_caract_more(carac, tmp, list));
	return (NULL);
}

static t_list		*ft_resize_cmd_for_dir(t_list **list, t_list *t,
					t_list *ret, int i)
{
	t_list	*back;
	t_list	*prev;

	if ((ft_count_nb_redir(t) > 0 || ft_count_nb_redir2(t) > 0)
	&& !(((t_tag *)(t->content))->tag != -62 &&
	((t_tag *)(t->content))->tag != -63
	&& ((t_tag *)(t->content))->tag != -60))
		ret = ft_change_first_caract(list);
	back = *list;
	prev = back;
	while (back && ++i)
	{
		t = prev;
		while (back && ((t_tag *)(back->content))->tag != -59)
			back = back->next;
		!i ? ft_remove_all_multi_dir(ft_count_nb_redir(t->next), t, i) : 0;
		!i ? ft_remove_all_multi_dirbis(ft_count_nb_redir(t->next), t, i) : 0;
		i ? 0 : ft_rmv_all_multi_dir2(ft_count_nb_redir2(t->next), t, i);
		i ? 0 : ft_remove_all_multi_dir2bis(ft_count_nb_redir2(t->next), t, i);
		prev = back;
		back && ((t_tag *)(back->content))->tag == -59 ? back = back->next : 0;
	}
	if (ret)
		return (ret);
	return (NULL);
}

static int			ft_free_more(t_list *lst)
{
	t_list	*n;

	if (lst)
	{
		n = lst->next;
		n->next = NULL;
		lst->next = NULL;
		ft_lstdelone(n, free);
		ft_lstdelone(lst, free);
	}
	return (1);
}

int					ft_verif_redir(t_list *list, t_list **command_list,
					t_list **env, char *com)
{
	t_list	*tmp;
	t_list	*free;
	int		i;

	free = NULL;
	if (ft_check_redir(command_list))
		return (ft_printf_fd(2, "\033[1;31mminishell\033[0m: error open \
		file\n"));
	free = ft_resize_cmd_for_dir(command_list, *command_list, NULL, -1);
	tmp = *command_list;
	if (((t_tag *)(tmp->content))->tag == -62 ||
		((t_tag *)(tmp->content))->tag == -63 ||
		((t_tag *)(tmp->content))->tag == -60)
		ft_remove_start_dir(command_list);
	ft_change_order_list(*command_list);
	tmp = *command_list;
	com = ((t_tag *)(tmp->content))->str;
	i = -1;
	while (com[++i])
		com[i] = ft_tolower(com[i]);
	list = tmp->next;
	if (command_cmp(list, command_list, env, com))
		return (ft_free_more(free));
	ft_free_more(free);
	return (0);
}
