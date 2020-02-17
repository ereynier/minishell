/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:08:20 by jacens            #+#    #+#             */
/*   Updated: 2020/02/14 11:39:27 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printffd.h"

static int		ft_verif_flag_fd(char verif)
{
	int		i;
	char	*flag;

	flag = "cspdiuxX";
	i = -1;
	while (flag[++i])
		if (flag[i] == verif)
			return (1);
	return (0);
}

static int		ft_check_flags_fd(int fd, const char *format, va_list *args,
								int *valprintf)
{
	int			i;
	t_printfd	*struc;

	struc = NULL;
	if (!(struc = ft_set_struct_fd(struc, fd)))
		return (-1);
	i = 0;
	if (format[i] == '%')
	{
		write(fd, &format[i], 1);
		*valprintf += 1;
		i += 1;
	}
	else if (format[i] >= '0' && format[i] <= '9')
		i += ft_with_pre_fd(&format[i], args, valprintf, struc);
	else if (format[i] == '.' || format[i] == '*' || format[i] == '-')
		i += ft_with_pre_fd(&format[i], args, valprintf, struc);
	else if (ft_verif_flag_fd(format[i]) == 1)
		i += ft_no_pre_fd(&format[i], args, valprintf, struc);
	ft_end_one_check_fd(struc);
	return (i);
}

static int		ft_write(int fd, const char *format)
{
	int i;

	i = ft_strlchr(format, '%');
	write(fd, format, i);
	return (i);
}

static int		ft_init(int fd, const char *format, va_list *args)
{
	int		i;
	int		j;
	int		valprintf;

	i = 0;
	valprintf = 0;
	while (format[i] != '\0')
	{
		j = 0;
		if (format[i] == '%')
		{
			i++;
			i += ft_check_flags_fd(fd, &format[i], args, &valprintf);
			if (valprintf == -1)
				return (-1);
		}
		if (format[i] != '\0')
			j += ft_write(fd, &format[i]);
		i += j;
		valprintf += j;
	}
	return (valprintf);
}

int				ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		valprintf;

	va_start(args, format);
	valprintf = ft_init(fd, format, &args);
	va_end(args);
	return (valprintf);
}
