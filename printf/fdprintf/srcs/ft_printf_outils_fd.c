/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_outils_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 17:03:32 by jacens            #+#    #+#             */
/*   Updated: 2020/02/14 11:39:27 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printffd.h"

void		ft_print_pre_fd(int *valprintf, t_printfd *struc, char *ptr,
			char format)
{
	char	c;

	c = 0;
	struc->left != 1 ? ft_print_space_fd(valprintf, struc) : 0;
	if (struc->zero > 0 && format != 's')
	{
		ft_print_zero_fd(valprintf, struc, ptr, format);
		if (ptr[0] == '-')
			ptr++;
	}
	format == 'c' && ptr[0] == '\0' ? write(struc->fd, &c, 1) :
	write(struc->fd, ptr, struc->print);
	*valprintf += struc->print;
	if (struc->left == 1)
		ft_print_space_fd(valprintf, struc);
}

void		ft_end_one_check_fd(t_printfd *struc)
{
	struc->arg = NULL;
	free(struc);
	struc = NULL;
}

t_printfd	*ft_set_struct_fd(t_printfd *struc, int fd)
{
	if (!(struc = malloc(sizeof(*struc))))
		return (NULL);
	struc->space = 0;
	struc->zero = -1;
	struc->left = 0;
	struc->print = -1;
	struc->intnull = 0;
	struc->dot = 0;
	struc->arg = NULL;
	struc->fd = fd;
	return (struc);
}
