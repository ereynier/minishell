/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 17:44:41 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 17:54:35 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**ft_lst_to_char(t_list *env)
{
	char	**envp;
	int		i;

	i = 0;
	(void)env;
	// i = ft_lstsize(env);
	// if (!(envp = malloc(i + 1)))
	// 	return (NULL);
	envp = NULL;
	return(envp);
}
