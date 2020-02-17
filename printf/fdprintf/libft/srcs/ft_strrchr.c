/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:32:56 by jacens            #+#    #+#             */
/*   Updated: 2020/02/14 11:39:27 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	last;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	last = 0;
	if (c == 0)
		return (ptr + ft_strlen(ptr));
	while (i != ft_strlen(ptr))
	{
		if (ptr[i] == (char)c)
			last = i;
		i++;
	}
	if (ptr[last] == (char)c)
		return (&ptr[last]);
	return (NULL);
}
