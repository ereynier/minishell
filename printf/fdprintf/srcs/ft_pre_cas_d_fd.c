/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_pre_cas_d.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 17:12:35 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 13:46:37 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printffd.h"

void	ft_cas_d_1bis_fd(t_printfd *struc, char *ptr, int *valprintf)
{
	if (struc->space == 0 && struc->zero == 0
	&& (ft_strcmp(ptr, "0") == 0))
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
	else
		ft_cas_d_2_fd(struc, ptr, valprintf);
}

void	ft_cas_d_2_fd(t_printfd *struc, char *ptr, int *valprintf)
{
	if (struc->zero == -1 && struc->space == 0 && struc->print == -1
	&& (ft_strcmp(ptr, "0") == 0))
	{
		struc->left = 0;
		struc->print = 0;
		struc->space = -1;
		struc->zero = 0;
	}
	else
		ft_cas_d_3_fd(struc, ptr, valprintf);
}

void	ft_cas_d_3_fd(t_printfd *struc, char *ptr, int *valprintf)
{
	if (struc->zero == -1 && struc->space == 0 && struc->print == -1
	&& ptr[0] == '-')
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
		struc->print = (int)ft_strlen(ptr);
		struc->zero -= 1;
	}
	else
		ft_cas_d_4_fd(struc, ptr, valprintf);
}

void	ft_cas_d_4_fd(t_printfd *struc, char *ptr, int *valprintf)
{
	if (struc->zero == -1 && struc->space == 0 && struc->print == -1)
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
	else
		ft_cas_d_5_fd(struc, ptr, valprintf);
}

void	ft_cas_d_5_fd(t_printfd *struc, char *ptr, int *valprintf)
{
	if (struc->zero < -1 && struc->space == 0)
	{
		struc->space < 0 ? struc->left = 1 : 0;
		struc->space < 0 ? struc->space *= -1 : 0;
		struc->zero < 0 && struc->print < 0 ? struc->print = 0 : 0;
		struc->zero < 0 ? struc->zero = 0 : 0;
		ptr[0] == '-' ? struc->zero += 1 : 0;
		struc->print = (int)ft_strlen(ptr);
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
		ft_cas_d_6_fd(struc, ptr, valprintf);
}
