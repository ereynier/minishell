/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_cas_d_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:15:45 by jacens            #+#    #+#             */
/*   Updated: 2020/02/14 11:39:26 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_cas_d_13(t_print *struc, char *ptr)
{
	if (!(struc->space == 0 && struc->zero == 0
	&& (ft_strcmp(ptr, "0") == 0)))
	{
		struc->space < 0 ? struc->left = 1 : 0;
		struc->space < 0 ? struc->space *= -1 : 0;
		struc->zero < 0 && struc->print < 0 ? struc->print = 0 : 0;
		struc->zero < 0 ? struc->zero = 0 : 0;
		ptr[0] == '-' ? struc->zero += 1 : 0;
		struc->print == -1 ? struc->print = (int)ft_strlen(ptr) : 0;
		struc->zero -= struc->print;
		struc->zero < 0 ? struc->zero = 0 : 0;
		struc->space -= (struc->print + struc->zero);
		if (struc->print == 0 && struc->space != -1)
		{
			struc->space -= ft_strlen(ptr);
			struc->print = ft_strlen(ptr);
		}
	}
}

void	ft_cas_d_7_1(t_print *struc, char *ptr, int *valprintf)
{
	if (struc->space > 0 && struc->print == -1 && struc->zero == 0 &&
	struc->left == 0 && (ft_strcmp(ptr, "0") == 0) && struc->dot == 1)
	{
		write(1, "0", 1);
		struc->space = 0;
		struc->zero = 0;
		struc->print = 1;
		*valprintf += 1;
	}
	else
		ft_cas_d_7_2(struc, ptr, valprintf);
}

void	ft_cas_d_7_2(t_print *struc, char *ptr, int *valprintf)
{
	if (struc->space < 0 && !(struc->zero == 0 && (ft_strcmp(ptr, "0")
	== 0)) && ptr[0] == '-')
	{
		struc->space < 0 ? struc->left = 1 : 0;
		struc->space < 0 ? struc->space *= -1 : 0;
		struc->zero < 0 && struc->print < 0 ? struc->print = 0 : 0;
		struc->zero < 0 ? struc->zero = 0 : 0;
		struc->print == -1 ? struc->print = (int)ft_strlen(ptr) : 0;
		struc->zero -= struc->print;
		struc->zero < 0 ? struc->zero = 0 : 0;
		struc->space -= (struc->print + struc->zero);
		if (struc->print == 0 && struc->space != -1)
		{
			struc->space -= ft_strlen(ptr);
			struc->print = ft_strlen(ptr);
		}
	}
	else
		ft_cas_d_8(struc, ptr, valprintf);
}
