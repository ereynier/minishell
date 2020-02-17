/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:03:21 by jacens            #+#    #+#             */
/*   Updated: 2020/02/17 14:46:11 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			call_command_norme(t_list **list, t_list ***command_list,
			t_list ***env, char **com)
{
	if (((t_tag *)((*list)->content))->tag == -61)
	{
		if (!check_line(*list))
		{
			preset_var(*list, **env, 0);
			fill_ret_env(**env, 0);
		}
		*list = (*list)->next;
	}
	else
	{
		*com = ((t_tag *)((*list)->content))->str;
		if (ft_verif_redir((*list)->next, list, *env, *com))
			return (1);
		while (*list && ((t_tag *)((*list)->content))->tag != -59
		&& ((t_tag *)((*list)->content))->tag != -61)
			*list = (*list)->next;
	}
	(void)command_list;
	return (0);
}
