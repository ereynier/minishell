/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:55:35 by jacens            #+#    #+#             */
/*   Updated: 2020/02/21 04:42:14 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list				*skip_redir_go_next_com(t_list *lst)
{
	while (lst && (((t_tag *)(lst->content))->tag == -62 ||
	((t_tag *)(lst->content))->tag == -63 ||
	((t_tag *)(lst->content))->tag == -60))
	{
		lst = lst->next->next;
		if (lst)
			lst = lst->next;
	}
	return (lst);
}

t_list				*skip_redir_to_go_next(t_list *lst)
{
	while (lst && (((t_tag *)(lst->content))->tag == -62 ||
	((t_tag *)(lst->content))->tag == -63 ||
	((t_tag *)(lst->content))->tag == -60))
	{
		lst = lst->next->next;
		if (lst)
			lst = lst->next;
	}
	if (lst)
		lst = lst->next;
	return (lst);
}

int					ft_verif_redir(t_list *list, t_list **command_list,
					t_list **env, char *com)
{
	t_list	*tmp;
	int		i;

	if (ft_check_redir(command_list))
		return (ft_printf_fd(2, "\033[1;31mminishell\033[0m: error open \
		file\n"));
	tmp = skip_redir_go_next_com(*command_list);
	com = tmp ? ((t_tag *)(tmp->content))->str : NULL;
	i = -1;
	if (com)
		while (com[++i])
			com[i] = ft_tolower(com[i]);
	list = *command_list;
	if (command_cmp(list, command_list, env, com))
		return (1);
	return (0);
}

t_list				*skip_redir_go_next(t_list *lst)
{
	lst = lst->next;
	while (lst && (((t_tag *)(lst->content))->tag == -62 ||
	((t_tag *)(lst->content))->tag == -63 ||
	((t_tag *)(lst->content))->tag == -60))
	{
		lst = lst->next->next;
		if (lst && ((t_tag *)(lst->content))->tag == -32)
			lst = lst->next;
	}
	return (lst);
}
