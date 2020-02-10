/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_pre_printf.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/15 16:59:43 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/12 02:48:06 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_with_dot(const char *format, va_list *args, t_print *struc)
{
	int i;

	i = -1;
	while (format[++i] == '-')
		struc->left = 1;
	if (format[i] >= '0' && format[i] <= '9')
		struc->space = ft_atoi(&format[i]);
	while (format[i] >= '0' && format[i] <= '9')
		i++;
	if (format[i] == '*')
	{
		struc->space = va_arg(*args, int);
		i++;
	}
	i++;
	if (format[i] >= '0' && format[i] <= '9')
		struc->zero = ft_atoi(&format[i]);
	while (format[i] >= '0' && format[i] <= '9')
		i++;
	if (format[i] == '*')
	{
		struc->zero = va_arg(*args, int);
		struc->zero < 0 && format[i + 1] == 's' ? struc->left = 1 : 0;
		struc->zero < 0 && format[i + 1] == 's' ? struc->zero *= -1 : 0;
	}
}

static void	ft_no_dot(const char *format, va_list *args, t_print *struc)
{
	int i;

	i = -1;
	while (format[++i] == '-')
		struc->left = 1;
	if (format[i] >= '1' && format[i] <= '9')
	{
		struc->space = ft_atoi(&format[i]);
		while (format[i] >= '0' && format[i] <= '9')
			i++;
	}
	else if (format[i] == '0' && format[i + 1] == '-')
	{
		ft_no_dot(&format[i + 1], args, struc);
	}
	else if (format[i] == '0' && format[i + 1] == '*')
	{
		struc->zero = va_arg(*args, int);
		struc->zero < 0 ? struc->left = 1 : 0;
		struc->zero < 0 ? struc->zero *= -1 : 0;
		i += 2;
	}
	else
		ft_do_more_config(format, args, struc, i);
}

static int	ft_check_dot(const char *format, va_list *args, t_print *struc)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while ((format[i] >= '0' && format[i] <= '9') ||
	(format[i] == '.' || format[i] == '*' || format[i] == '-'))
	{
		if (format[i] == '.')
			j++;
		i++;
	}
	if (j > 0)
	{
		struc->dot = 1;
		ft_with_dot(format, args, struc);
	}
	else
		ft_no_dot(format, args, struc);
	return (i);
}

int			ft_with_pre(const char *format, va_list *args, int *valprintf,
						t_print *struc)
{
	char	*ptr;
	int		i;

	i = ft_check_dot(format, args, struc);
	ptr = ft_config_flags(args, format[i], valprintf, struc);
	if (ptr == NULL)
		return (-1);
	ft_more_config_struc(struc, format[i], ptr);
	struc->space < 0 && struc->zero > 0 && struc->left == 1 && struc->dot == 1
	&& format[i] != 's' ? struc->zero = 0 : 0;
	format[i] == '%' ? struc->zero = 0 : 0;
	format[i] == 'c' || format[i] == 'p' ?
	ft_config_stru3(valprintf, struc, ptr, format[i]) : 0;
	format[i] == 'd' || format[i] == 'i' || format[i] == 'x' ||
	format[i] == 'X' || format[i] == 'u' || format[i] == '%' ?
	ft_config_stru4(struc, ptr, valprintf, format[i]) : 0;
	struc->dot == 1 && format[i] == 's' ?
	ft_config_stru(struc, ptr) : 0;
	struc->dot == 0 && format[i] == 's' ?
	ft_config_stru2(struc, ptr) : 0;
	ft_with_pre_do(format[i], valprintf, ptr, struc);
	free(ptr);
	return (++i);
}

int			ft_no_pre(const char *format, va_list *args, int *valprintf,
					t_print *struc)
{
	char	*ptr;
	int		i;

	ptr = ft_config_flags(args, format[0], valprintf, struc);
	if (ptr != NULL || format[0] == 'c')
	{
		i = 1;
		if (format[0] == 'c' && ptr[0] == 0)
			write(1, "\0", 1);
		else
		{
			i = ft_strlen(ptr);
			write(1, ptr, i);
		}
		*valprintf += i;
		free(ptr);
		return (1);
	}
	return (-1);
}
