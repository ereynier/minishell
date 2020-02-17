/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:08:20 by jacens            #+#    #+#             */
/*   Updated: 2020/02/14 11:39:26 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_verif_flag(char *flag, char verif)
{
	int i;

	i = -1;
	while (flag[++i])
		if (flag[i] == verif)
			return (1);
	return (0);
}

static int		ft_check_flags(const char *format, va_list *args, char *flag,
								int *valprintf)
{
	int		i;
	t_print	*struc;

	struc = NULL;
	if (!(struc = ft_set_struct(struc)))
		return (-1);
	i = 0;
	if (format[i] == '%')
	{
		write(1, &format[i], 1);
		*valprintf += 1;
		i += 1;
	}
	else if (format[i] >= '0' && format[i] <= '9')
		i += ft_with_pre(&format[i], args, valprintf, struc);
	else if (format[i] == '.' || format[i] == '*' || format[i] == '-')
		i += ft_with_pre(&format[i], args, valprintf, struc);
	else if (ft_verif_flag(flag, format[i]) == 1)
		i += ft_no_pre(&format[i], args, valprintf, struc);
	ft_end_one_check(struc);
	return (i);
}

static int		ft_write(const char *format)
{
	int i;

	i = ft_strlchr(format, '%');
	write(1, format, i);
	return (i);
}

static int		ft_init(const char *format, va_list *args, char *flag)
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
			i += ft_check_flags(&format[i], args, flag, &valprintf);
			if (valprintf == -1)
				return (-1);
		}
		if (format[i] != '\0')
			j += ft_write(&format[i]);
		i += j;
		valprintf += j;
	}
	return (valprintf);
}

int				ft_printf(const char *format, ...)
{
	va_list	args;
	int		valprintf;
	char	*flag;

	if ((flag = ft_strdup("cspdiuxX")) == NULL)
		return (-1);
	va_start(args, format);
	valprintf = ft_init(format, &args, flag);
	va_end(args);
	free(flag);
	return (valprintf);
}
