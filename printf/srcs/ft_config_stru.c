/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_config_stru.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 13:34:53 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/12 02:47:41 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_config_stru(t_print *struc, char *ptr)
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

void		ft_config_stru2(t_print *struc, char *ptr)
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

void		ft_config_stru3(int *valprintf, t_print *struc, char *ptr,
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

void		ft_config_stru4(t_print *struc, char *ptr, int *valprintf,
							char format)
{
	if (struc->space == 0 && struc->zero == 0 && struc->print < 0
	&& (ft_strcmp(ptr, "0") == 0) && format == 'i' && format == 'd')
	{
		write(1, "0", 1);
		*valprintf += 1;
	}
	else if (struc->space == 0 && struc->zero == 0 && struc->print == -1
	&& (ft_strcmp(ptr, "0") == 0) && struc->dot == 0)
	{
		write(1, "0", 1);
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
		ft_cas_d_1(struc, ptr, valprintf);
}
