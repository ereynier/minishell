/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_count_nbr.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/15 15:15:57 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 13:21:26 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_count_nbr(long long n)
{
	long long	i;
	long long	count;

	count = 1;
	i = 10;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n >= i)
	{
		i *= 10;
		count++;
	}
	return (count);
}
