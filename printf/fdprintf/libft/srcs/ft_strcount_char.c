/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcount_char.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/16 22:13:32 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 13:21:26 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_strcount_char(char *str, char find)
{
	int nb;
	int i;

	nb = 0;
	i = -1;
	while (str[++i])
		if (str[i] == find)
			nb++;
	return (nb);
}
