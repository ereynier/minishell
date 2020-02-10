/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_outils3.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/03 12:15:42 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 13:43:53 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printffd.h"

void		ft_more_config_struc_fd(t_printfd *struc, char format, char *ptr)
{
	if (struc->left == 0 && struc->space > 0 && struc->zero == 0 &&
	struc->dot == 1)
		struc->dot = 0;
	if (struc->left == 1 && struc->space == 0 && struc->zero > 0 &&
	struc->zero < (int)ft_strlen(ptr) && format == 's')
	{
		struc->space = struc->zero;
		struc->zero = 0;
		struc->left == 1 && struc->space > 0 && struc->zero == 0 &&
		struc->dot == 1 && struc->space > 0 &&
		struc->space != (int)ft_strlen(ptr) ?
		struc->zero = (int)ft_strlen(ptr) : 0;
	}
	if (struc->dot == 1 && struc->left == 1 && struc->space == 0 &&
	struc->zero > 0 && format != 's' && (ft_strcmp(ptr, "0") == 0))
	{
		struc->space = 0;
		struc->zero = 0;
		struc->print = 0;
	}
	ft_more_config_struc2_fd(struc, format, ptr);
}

void		ft_more_config_struc2_fd(t_printfd *struc, char format, char *ptr)
{
	if (struc->dot == 1 && struc->left == 1 && struc->space == 0 &&
	struc->zero > 0 && format != 's')
	{
		struc->space = 0;
		struc->zero = 0;
		struc->left = 0;
	}
	if (struc->dot == 0 && struc->left == 1 && struc->space == 0 &&
	struc->zero > 0 && format != 's' && (ft_strcmp(ptr, "0") == 0))
	{
		struc->space = struc->zero;
		struc->zero = 0;
		struc->left == 1 && struc->space > 0 && struc->zero == 0 &&
		struc->dot == 1 && struc->space > 0 &&
		struc->space != (int)ft_strlen(ptr) ?
		struc->zero = (int)ft_strlen(ptr) : 0;
	}
	ft_more_config_struc3_fd(struc, format, ptr);
}

void		ft_more_config_struc3_fd(t_printfd *struc, char format, char *ptr)
{
	if (struc->dot == 0 && struc->left == 1 && struc->space == 0 &&
	struc->zero > 0 && format != 's' && !(ft_strcmp(ptr, "0") == 0))
	{
		struc->space = struc->zero;
		struc->zero = 0;
		struc->left == 1 && struc->space > 0 && struc->zero == 0 &&
		struc->dot == 1 && struc->space > 0 &&
		struc->space != (int)ft_strlen(ptr) ?
		struc->zero = (int)ft_strlen(ptr) : 0;
	}
}
