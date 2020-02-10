/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_pre_printf_fd.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/15 16:59:43 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 18:15:22 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printffd.h"

static void	ft_with_dot(const char *format, va_list *args, t_printfd *struc)
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

static void	ft_no_dot(const char *format, va_list *args, t_printfd *struc)
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
		ft_do_more_config_fd(format, args, struc, i);
}

static int	ft_check_dot(const char *format, va_list *args, t_printfd *struc)
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

int			ft_with_pre_fd(const char *format, va_list *args, int *valprintf,
						t_printfd *struc)
{
	char	*ptr;
	int		i;

	i = ft_check_dot(format, args, struc);
	ptr = ft_config_flags_fd(args, format[i], valprintf, struc);
	if (ptr == NULL)
		return (-1);
	ft_more_config_struc_fd(struc, format[i], ptr);
	struc->space < 0 && struc->zero > 0 && struc->left == 1 && struc->dot == 1
	&& format[i] != 's' ? struc->zero = 0 : 0;
	format[i] == '%' ? struc->zero = 0 : 0;
	format[i] == 'c' || format[i] == 'p' ?
	ft_config_stru3_fd(valprintf, struc, ptr, format[i]) : 0;
	format[i] == 'd' || format[i] == 'i' || format[i] == 'x' ||
	format[i] == 'X' || format[i] == 'u' || format[i] == '%' ?
	ft_config_stru4_fd(struc, ptr, valprintf, format[i]) : 0;
	struc->dot == 1 && format[i] == 's' ?
	ft_config_stru_fd(struc, ptr) : 0;
	struc->dot == 0 && format[i] == 's' ?
	ft_config_stru2_fd(struc, ptr) : 0;
	ft_with_pre_do_fd(format[i], valprintf, ptr, struc);
	free(ptr);
	return (++i);
}

int			ft_no_pre_fd(const char *format, va_list *args, int *valprintf,
					t_printfd *struc)
{
	char	*ptr;
	int		i;

	ptr = ft_config_flags_fd(args, format[0], valprintf, struc);
	if (ptr != NULL || format[0] == 'c')
	{
		i = 1;
		if (format[0] == 'c' && ptr[0] == 0)
			write(struc->fd, "\0", 1);
		else
		{
			i = ft_strlen(ptr);
			write(struc->fd, ptr, i);
		}
		*valprintf += i;
		free(ptr);
		return (1);
	}
	return (-1);
}
