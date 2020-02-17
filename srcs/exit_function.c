/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:40:00 by ereynier          #+#    #+#             */
/*   Updated: 2020/02/17 12:00:24 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			fill_ret_env(t_list *env, int ret)
{
	char *str;

	while ((strcmp("?", ((t_tag *)(env->content))->str)))
		env = env->next;
	free(((t_tag *)(env->content))->value);
	if (!(str = ft_itoa((unsigned char)ret)))
		return (1);
	((t_tag *)(env->content))->value = str;
	return (0);
}

void		exit_command(t_list *list, t_list **command_list, t_list **env,
			unsigned char i)
{
	ft_printf("exit\n");
	if (list && list->next)
	{
		list = list->next;
		while (ft_isdigit(((t_tag *)(list->content))->str[i]))
			i++;
		if ((((t_tag *)(list->content))->str[i]))
		{
			i = 255;
			ft_printf_fd(2, "\033[1;31mminishell\033[0m: exit: %s: \
			numeric argment required\n", ((t_tag *)(list->content))->str);
		}
		else if (list->next && list->next->next)
		{
			ft_printf_fd(2,
			"\033[1;31mminishell\033[0m: exit: to many arguments\n");
			return ;
		}
		else
			i = (unsigned char)ft_atoi(((t_tag *)(list->content))->str);
	}
	ft_lstclear(command_list, &free);
	ft_lstclear(env, &free);
	exit(i);
}
