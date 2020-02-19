/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:03:21 by jacens            #+#    #+#             */
/*   Updated: 2020/02/17 19:52:06 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_getvalue(char *str, t_list *env)
{
	while (env)
	{
		if (!ft_strcmp(((t_tag *)(env->content))->str, str))
			return (((t_tag *)(env->content))->value);
		env = env->next;
	}
	return ("");
}

static char	*get_env_var(char *buf, t_list *env)
{
	char	*str;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	if (!(str = ft_calloc(1, 1)))
		return (0);
	while (1)
	{
		if (!(tmp = ft_calloc(1, 1)))
			return (0);
		while ((buf[i] == '\\' && buf[i + 1] == '$' && i++) ||
		(buf[i] && buf[i] != '$') || (i > 0 && buf[i - 1] == '\\'))
			str = ft_append(str, &buf[i++], 1);
		if (!buf[i])
			return (love_the_norme(str, tmp));
		j = ++i;
		while (((buf[i] && ft_isalpha(buf[i])) ||
			(buf[i] == '?' && !buf[j + 1])))
			tmp = ft_append(tmp, &buf[i++], 1);
		str = ft_append(str,
		ft_getvalue(tmp, env), ft_strlen(ft_getvalue(tmp, env)));
		free(tmp);
	}
}

char		*append_line(t_list **command_list, t_list *env)
{
	char *str;
	char *buf;

	if (!(str = malloc(1)))
		return (0);
	str[0] = 0;
	while (*command_list && ((t_tag *)((*command_list)->content))->tag >= 0)
	{
		buf = ((t_tag *)((*command_list)->content))->str;
		if (((t_tag *)((*command_list)->content))->tag == 39)
			str = ft_append(str, buf, ft_strlen(buf));
		else
		{
			buf = get_env_var(buf, env);
			str = ft_append(str, buf, ft_strlen(buf));
			free(buf);
		}
		*command_list = (*command_list)->next;
	}
	return (str);
}

static void	reconfig_norme(t_list ***command_list, t_list **env, t_list **tmp)
{
	int		nb;
	char	*str;
	t_list	*prev;

	nb = ((t_tag *)((**command_list)->content))->tag;
	str = append_line(*command_list, *env);
	free(((t_tag *)((*tmp)->content))->str);
	((t_tag *)((*tmp)->content))->str = str;
	((t_tag *)((*tmp)->content))->value = 0;
	((t_tag *)((*tmp)->content))->tag = nb;
	while (*tmp && (*tmp)->next &&
		((t_tag *)((*tmp)->next->content))->tag >= 0)
	{
		prev = *tmp;
		(*tmp) = (*tmp)->next;
		prev->next = (*tmp)->next;
		ft_lstdelone(*tmp, free);
		*tmp = prev;
	}
}

int			reconfig_command(t_list **command_list, t_list *env)
{
	t_list	*tmp;
	t_list	*start;

	tmp = *command_list;
	start = tmp;
	while (*command_list)
	{
		if (((t_tag *)(tmp->content))->tag >= 0)
		{
			reconfig_norme(&command_list, &env, &tmp);
		}
		else
			*command_list = (*command_list)->next;
		tmp = (tmp)->next;
	}
	*command_list = start;
	return (0);
}
