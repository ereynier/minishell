/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_count_nbr_base.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/15 15:16:59 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 13:21:26 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_count_nbr_base(long long n, int len)
{
	long long	i;
	long long	count;

	count = 1;
	i = len;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n >= i)
	{
		i *= len;
		count++;
	}
	return (count);
}
