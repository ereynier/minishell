/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_pwd.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/07 17:35:20 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 17:35:27 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_get_pwd(void)
{
	int		i;
	char	*buf;

	i = 5;
	if (!(buf = malloc(i)))
		return (0);
	while (!getcwd(buf, i))
	{
		if (errno != ERANGE)
			return (0);
		i += 5;
		free(buf);
		buf = malloc(i);
	}
	return (buf);
}
