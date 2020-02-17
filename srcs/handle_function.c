/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 06:29:53 by jacens            #+#    #+#             */
/*   Updated: 2020/02/17 14:53:11 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig)
{
	char	*cp;
	char	*path;

	if (sig == SIGINT || sig == SIGQUIT)
	{
		ft_printf("\033[2D");
		ft_printf("  ");
		ft_printf("\033[2D");
		cp = ft_get_pwd();
		path = ft_strdup(ft_strrchr(cp, 47));
		free(cp);
		ft_printf("\n\033[1;31m➜  ");
		ft_printf("\033[1;36m%s \033[1;33m✗ \033[0m", &path[1]);
		free(path);
	}
}
