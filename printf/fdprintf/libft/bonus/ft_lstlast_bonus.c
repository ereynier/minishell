/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:00:19 by jacens            #+#    #+#             */
/*   Updated: 2020/02/14 11:39:27 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list		*ft_lstlast(t_list *lst)
{
	t_list	*beg_lst;

	if (lst == NULL)
		return (NULL);
	beg_lst = lst;
	while (beg_lst->next != NULL)
		beg_lst = beg_lst->next;
	return (beg_lst);
}
