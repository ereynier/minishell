/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_stru_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 13:34:53 by jacens            #+#    #+#             */
/*   Updated: 2020/02/14 11:39:26 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printffd.h"

void		ft_config_stru_fd(t_printfd *struc, char *ptr)
{
	struc->space < 0 ? struc->left = 1 : 0;
	struc->space < 0 ? struc->space *= -1 : 0;
	struc->space == 0 && struc->zero == 0 ? struc->print = 0 : 0;
	struc->space > 0 && struc->zero == 0 &&
	struc->print == -1 ? struc->print = 0 : 0;
	struc->zero > (int)ft_strlen(ptr) && struc->space == 0 ?
	struc->zero = (int)ft_strlen(ptr) : 0;
	struc->print == -1 ? struc->print = 0 : 0;
	struc->zero > 0 && struc->space == 0 ?
	struc->space = struc->zero : 0;
	struc->zero > 0 && struc->space != 0 ?
	struc->print = struc->zero : 0;
	struc->zero > 0 ? struc->zero = 0 : 0;
	struc->zero >= 0 && struc->space > 0 ? struc->space -=
	(struc->print + struc->zero) : 0;
	struc->space == 0 && struc->zero == -1 ? struc->print = 0 : 0;
	struc->zero < 0 && struc->space > 0 ? struc->space -= struc->print : 0;
	struc->print > (int)ft_strlen(ptr) ? struc->space += struc->print -
	(int)ft_strlen(ptr) : 0;
	struc->print > (int)ft_strlen(ptr) ? struc->print =
	(int)ft_strlen(ptr) : 0;
}

void		ft_config_stru2_fd(t_printfd *struc, char *ptr)
{
	struc->space < 0 ? struc->left = 1 : 0;
	struc->space < 0 ? struc->space *= -1 : 0;
	struc->space == 0 && struc->zero == 0 ? struc->print = 0 : 0;
	struc->space > 0 && struc->zero == 0 &&
	struc->print == -1 ? struc->print = 0 : 0;
	struc->zero > (int)ft_strlen(ptr) && struc->space == 0 ?
	struc->zero = (int)ft_strlen(ptr) : 0;
	struc->print == -1 ? struc->print = (int)ft_strlen(ptr)
	: 0;
	struc->zero > 0 && struc->space == 0 ?
	struc->space = struc->zero : 0;
	struc->zero > 0 && struc->space != 0 ?
	struc->print = struc->zero : 0;
	struc->zero > 0 ? struc->zero = 0 : 0;
	struc->zero >= 0 && struc->space > 0 ? struc->space -=
	(struc->print + struc->zero) : 0;
	struc->zero < 0 && struc->space > 0 ? struc->space -= struc->print : 0;
	struc->print > (int)ft_strlen(ptr) ? struc->space += struc->print -
	(int)ft_strlen(ptr) : 0;
	struc->print > (int)ft_strlen(ptr) ? struc->print = (int)ft_strlen(ptr) : 0;
}

void		ft_config_stru3_fd(int *valprintf, t_printfd *struc, char *ptr,
							char format)
{
	struc->zero < 0 ? struc->zero = 0 : 0;
	struc->space < 0 ? struc->left = 1 : 0;
	struc->space < 0 ? struc->space *= -1 : 0;
	struc->space == 0 && struc->zero == 0 ? struc->print = 0 : 0;
	format != 's' && ptr[0] == '-' ? struc->zero += 1 : 0;
	format != 's' && struc->print == -1 ?
	struc->print = (int)ft_strlen(ptr) : 0;
	format == 'c' && ptr[0] == '\0' ? struc->space -= 1 : 0;
	format == 'c' && ptr[0] == '\0' ? *valprintf += 1 : 0;
	format != 's' ? struc->zero -= struc->print : 0;
	format != 's' && struc->zero < 0 ? struc->zero = 0 : 0;
	struc->space -= (struc->print + struc->zero);
	if (!(format == 'p' && (ft_strcmp(ptr, "0x0") == 0) && struc->print == 0))
	{
		struc->intnull == 1 && struc->zero == 0 && struc->space
		!= -1 ? struc->space += 1 : 0;
		struc->intnull == 1 && struc->zero == 0 && struc->space
		!= -1 ? *valprintf -= 1 : 0;
		struc->intnull == 1 && struc->zero == 0 && struc->space
		!= -1 ? ptr[0] = '\0' : 0;
		struc->print == 0 ? struc->print = ft_strlen(ptr) : 0;
	}
}

void		ft_config_stru4_fd(t_printfd *struc, char *ptr, int *valprintf,
							char format)
{
	if (struc->space == 0 && struc->zero == 0 && struc->print < 0
	&& (ft_strcmp(ptr, "0") == 0) && format == 'i' && format == 'd')
	{
		write(struc->fd, "0", 1);
		*valprintf += 1;
	}
	else if (struc->space == 0 && struc->zero == 0 && struc->print == -1
	&& (ft_strcmp(ptr, "0") == 0) && struc->dot == 0)
	{
		write(struc->fd, "0", 1);
		*valprintf += 1;
	}
	else if (struc->space == 0 && struc->zero == 0 && struc->print == -1
	&& (ft_strcmp(ptr, "0") == 0))
	{
		struc->left = 0;
		struc->print = 0;
		struc->space = -1;
		struc->zero = 0;
	}
	else
		ft_cas_d_1_fd(struc, ptr, valprintf);
}
