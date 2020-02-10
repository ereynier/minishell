/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 11:25:04 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 13:21:26 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dest;
	char	*ptr;

	if (dst == NULL && src == NULL)
		return (NULL);
	dest = (char *)dst;
	ptr = (char *)src;
	i = 0;
	while (i != n)
	{
		dest[i] = ptr[i];
		i++;
	}
	return (dest);
}
