/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:43:20 by jacens            #+#    #+#             */
/*   Updated: 2020/02/14 14:08:37 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	if (((t_tag *)lst->content)->str)
		del(((t_tag *)lst->content)->str);
	if (((t_tag *)lst->content)->value)
		del(((t_tag *)lst->content)->value);
	del(lst->content);
	free(lst);
}
