/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_outils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:42:45 by jacens            #+#    #+#             */
/*   Updated: 2020/02/14 11:39:26 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_do_more_config(const char *format, va_list *args,
								t_print *struc, int i)
{
	if (format[i] == '0')
	{
		struc->zero = ft_atoi(&format[i]);
		while (format[i] >= '0' && format[i] <= '9')
			i++;
	}
	else if (format[i] == '*')
		struc->space = va_arg(*args, int);
}

void		ft_print_space(int *valprintf, t_print *struc)
{
	int i;

	i = 0;
	while (struc->space > i)
	{
		write(1, " ", 1);
		*valprintf += 1;
		i++;
	}
}

void		ft_print_zero(int *valprintf, t_print *struc, char *ptr,
							char format)
{
	int		i;

	i = 0;
	if (ptr[0] == '-' && format != 's')
	{
		write(1, "-", 1);
		ptr++;
		struc->print -= 1;
		*valprintf += 1;
	}
	while ((struc->zero > i))
	{
		write(1, "0", 1);
		*valprintf += 1;
		i++;
	}
}

static void	ft_with_pre_do2(char format, int *valprintf, char *ptr,
						t_print *struc)
{
	if (format != 's' && (ft_strcmp(ptr, "0") == 0) && struc->print == 0)
	{
		struc->space += 1;
		struc->left != 1 ? ft_print_space(valprintf, struc) : 0;
		struc->left == 1 ? ft_print_space(valprintf, struc) : 0;
	}
	else if (format != 's' && (ft_strcmp(ptr, "0") == 0))
	{
		;
	}
	else if (format != 's')
	{
		ft_print_pre(valprintf, struc, ptr, format);
	}
	else
	{
		struc->left != 1 ? ft_print_space(valprintf, struc) : 0;
		write(1, ptr, struc->print);
		*valprintf += struc->print;
		struc->left == 1 ? ft_print_space(valprintf, struc) : 0;
	}
}

void		ft_with_pre_do(char format, int *valprintf, char *ptr,
						t_print *struc)
{
	if (format == 'p' && (ft_strcmp(ptr, "0x0") == 0) && struc->print == 0)
	{
		write(1, "0x", 2);
		*valprintf += 2;
	}
	else if (format != 's' && (ft_strcmp(ptr, "0") == 0) &&
			struc->zero == 0 && struc->space != 0 && struc->print == 0)
	{
		struc->left != 1 ? ft_print_space(valprintf, struc) : 0;
		ft_print_zero(valprintf, struc, ptr, format);
		struc->left == 1 ? ft_print_space(valprintf, struc) : 0;
	}
	else if (format != 's' && (ft_strcmp(ptr, "0") == 0) && (struc->zero != 0
		|| struc->space != 0) && struc->print != 0)
	{
		struc->left != 1 ? ft_print_space(valprintf, struc) : 0;
		ft_print_zero(valprintf, struc, ptr, format);
		write(1, "0", 1);
		struc->left == 1 ? ft_print_space(valprintf, struc) : 0;
		*valprintf += 1;
	}
	else
		ft_with_pre_do2(format, valprintf, ptr, struc);
}
