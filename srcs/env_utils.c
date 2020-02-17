/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 06:29:53 by jacens            #+#    #+#             */
/*   Updated: 2020/02/14 15:22:42 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			check_env(t_list *list, t_list *env)
{
	int i;

	i = 0;
	while (((t_tag *)(list->content))->str[i] &&
	((t_tag *)(list->content))->str[i] != '=')
		i++;
	if (((t_tag *)(list->content))->str[i])
		i++;
	while (env)
	{
		if (!ft_strncmp(((t_tag *)(list->content))->str,
			((t_tag *)(env->content))->str, i))
		{
			((t_tag *)(env->content))->tag = 1;
			if (((t_tag *)(list->content))->str[i])
			{
				free(((t_tag *)(env->content))->value);
				((t_tag *)(env->content))->value =
					ft_strdup(&((t_tag *)(list->content))->str[i]);
			}
			return (2);
		}
		env = env->next;
	}
	return (0);
}

void		print_export(t_list *env)
{
	char	**envp;
	int		i;
	int		j;

	i = 0;
	envp = ft_lst_to_char(env);
	envp = ft_sortup(envp);
	while (envp[i])
	{
		ft_printf("declare -x ");
		j = 0;
		while (envp[i][j] != '=')
		{
			ft_putchar(envp[i][j]);
			j++;
		}
		j++;
		ft_printf("=\"%s\"\n", &envp[i][j]);
		free(envp[i]);
		i++;
	}
	free(envp);
}
