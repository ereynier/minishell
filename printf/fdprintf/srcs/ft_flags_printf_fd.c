/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_printf_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:11:54 by jacens            #+#    #+#             */
/*   Updated: 2020/02/14 11:39:26 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printffd.h"

static char		*ft_do_flag4(va_list *args, int *valprintf, t_printfd *struc)
{
	char	*str;

	str = NULL;
	if (struc->arg[0] == 's')
	{
		if (!(str = ft_va_null_char_fd(args, struc)))
		{
			*valprintf = -1;
			return (NULL);
		}
	}
	return (str);
}

static char		*ft_do_flag3(va_list *args, int *valprintf, t_printfd *struc)
{
	char	*str;
	char	*ptr;

	str = NULL;
	if (struc->arg[0] == 'p')
	{
		if (!(ptr = ft_uitoa_base(va_arg(*args, void*), "0123456789abcdef")))
			*valprintf = -1;
		if (ptr != NULL)
		{
			if (!(str = ft_strjoin("0x", ptr)))
				*valprintf = -1;
			if (ptr != NULL)
				free(ptr);
		}
	}
	free(struc->arg);
	struc->arg = NULL;
	return (str);
}

static char		*ft_do_flag2(va_list *args, int *valprintf, t_printfd *struc)
{
	char	*str;

	str = NULL;
	if (struc->arg[0] == 'c')
	{
		if (!(str = malloc(2)))
			*valprintf = -1;
		else
		{
			str[0] = va_arg(*args, int);
			str[1] = '\0';
		}
	}
	else if (struc->arg[0] == 'u')
	{
		if (!(str = ft_uitoa(va_arg(*args, unsigned int))))
			*valprintf = -1;
	}
	free(struc->arg);
	struc->arg = NULL;
	return (str);
}

static char		*ft_do_flag(va_list *args, int *valprintf, t_printfd *struc)
{
	char	*str;

	str = NULL;
	if (struc->arg[0] == 'd' || struc->arg[0] == 'i')
	{
		if (!(str = ft_itoa(ft_va_null_int_fd(args, struc))))
			*valprintf = -1;
	}
	else if (struc->arg[0] == 'x')
	{
		if (!(str = ft_itoa_base(va_arg(*args, unsigned int),
								"0123456789abcdef")))
			*valprintf = -1;
	}
	else if (struc->arg[0] == 'X')
	{
		if (!(str = ft_itoa_base(va_arg(*args, unsigned int),
								"0123456789ABCDEF")))
			*valprintf = -1;
	}
	free(struc->arg);
	struc->arg = NULL;
	return (str);
}

char			*ft_config_flags_fd(va_list *args, char format, int *valprintf,
								t_printfd *struc)
{
	char	*str;

	str = NULL;
	if (!(struc->arg = ft_strdup(&format)))
	{
		*valprintf = -1;
		return (NULL);
	}
	if (format == '%')
		if (!(str = ft_strdup("%")))
			return (NULL);
	if (format == 'd' || format == 'i' || format == 'x' || format == 'X')
		str = ft_do_flag(args, valprintf, struc);
	if (format == 'c' || format == 'u')
		str = ft_do_flag2(args, valprintf, struc);
	if (format == 'p')
		str = ft_do_flag3(args, valprintf, struc);
	else if (format == 's')
		str = ft_do_flag4(args, valprintf, struc);
	if (format == 's' || format == '%')
	{
		free(struc->arg);
		struc->arg = NULL;
	}
	return (str);
}
