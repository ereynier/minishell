/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_outils2.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/21 18:42:45 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 13:43:49 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printffd.h"

void		ft_do_more_config_fd(const char *format, va_list *args,
								t_printfd *struc, int i)
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

void		ft_print_space_fd(int *valprintf, t_printfd *struc)
{
	int i;

	i = 0;
	while (struc->space > i)
	{
		write(struc->fd, " ", 1);
		*valprintf += 1;
		i++;
	}
}

void		ft_print_zero_fd(int *valprintf, t_printfd *struc, char *ptr,
							char format)
{
	int		i;

	i = 0;
	if (ptr[0] == '-' && format != 's')
	{
		write(struc->fd, "-", 1);
		ptr++;
		struc->print -= 1;
		*valprintf += 1;
	}
	while ((struc->zero > i))
	{
		write(struc->fd, "0", 1);
		*valprintf += 1;
		i++;
	}
}

static void	ft_with_pre_do2_fd(char format, int *valprintf, char *ptr,
						t_printfd *struc)
{
	if (format != 's' && (ft_strcmp(ptr, "0") == 0) && struc->print == 0)
	{
		struc->space += 1;
		struc->left != 1 ? ft_print_space_fd(valprintf, struc) : 0;
		struc->left == 1 ? ft_print_space_fd(valprintf, struc) : 0;
	}
	else if (format != 's' && (ft_strcmp(ptr, "0") == 0))
	{
		;
	}
	else if (format != 's')
	{
		ft_print_pre_fd(valprintf, struc, ptr, format);
	}
	else
	{
		struc->left != 1 ? ft_print_space_fd(valprintf, struc) : 0;
		write(struc->fd, ptr, struc->print);
		*valprintf += struc->print;
		struc->left == 1 ? ft_print_space_fd(valprintf, struc) : 0;
	}
}

void		ft_with_pre_do_fd(char format, int *valprintf, char *ptr,
						t_printfd *struc)
{
	if (format == 'p' && (ft_strcmp(ptr, "0x0") == 0) && struc->print == 0)
	{
		write(struc->fd, "0x", 2);
		*valprintf += 2;
	}
	else if (format != 's' && (ft_strcmp(ptr, "0") == 0) &&
			struc->zero == 0 && struc->space != 0 && struc->print == 0)
	{
		struc->left != 1 ? ft_print_space_fd(valprintf, struc) : 0;
		ft_print_zero_fd(valprintf, struc, ptr, format);
		struc->left == 1 ? ft_print_space_fd(valprintf, struc) : 0;
	}
	else if (format != 's' && (ft_strcmp(ptr, "0") == 0) && (struc->zero != 0
		|| struc->space != 0) && struc->print != 0)
	{
		struc->left != 1 ? ft_print_space_fd(valprintf, struc) : 0;
		ft_print_zero_fd(valprintf, struc, ptr, format);
		write(struc->fd, "0", 1);
		struc->left == 1 ? ft_print_space_fd(valprintf, struc) : 0;
		*valprintf += 1;
	}
	else
		ft_with_pre_do2_fd(format, valprintf, ptr, struc);
}
