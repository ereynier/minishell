/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   commande_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/07 15:03:21 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 13:41:36 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_getvalue(char *str, t_list *env)
{
	while(env)
	{
		if (!ft_strcmp(((t_tag *)(env->content))->str, str))
			return (((t_tag *)(env->content))->value);
		env = env->next;
	}
	return ("");
}


static char *get_env_var(char *buf, t_list *env)
{
	char *str;
	char *tmp;
	int i;

	i = 0;
	if (!(str = malloc(1)))
		return (0);
	str[0] = 0;
	while (1)
	{
		if (!(tmp = malloc(1)))
			return (0);
		tmp[0] = 0;
		while (buf[i] && buf[i] != '$')
			str = ft_append(str, &buf[i++], 1);
		if (!buf[i])
			return (str);
		i++;
		while (buf[i] && ft_isalnum(buf[i]))
			tmp = ft_append(tmp, &buf[i++], 1);
		str = ft_append(str,
		ft_getvalue(tmp, env), ft_strlen(ft_getvalue(tmp, env)));
		free(tmp);
	}
}

char 		*append_line(t_list **command_list, t_list *env)
{
	char *str;
	char *buf;
	if (!(str = malloc(1)))
			return (0);
		str[0] = 0;
	while (*command_list && ((t_tag *)((*command_list)->content))->tag >= 0)
	{
		buf = ((t_tag *)((*command_list)->content))->str;
		if (((t_tag *)((*command_list)->content))->tag != 34 &&
		((t_tag *)((*command_list)->content))->str[0] != '$')
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

int			reconfig_command(t_list **command_list, t_list *env, int nb)
{
	char	*str;
	t_list	*prev;
	t_list	*tmp;
	t_list	*start;

	tmp = *command_list;
	start = tmp;
	while (*command_list)
	{
		if (((t_tag *)(tmp->content))->tag >= 0)
		{
			nb = ((t_tag *)((*command_list)->content))->tag;
			str = append_line(command_list, env);
			free(((t_tag *)(tmp->content))->str);
			((t_tag *)(tmp->content))->str = str;
			((t_tag *)(tmp->content))->value = 0;
			((t_tag *)(tmp->content))->tag = nb;
			while (tmp && tmp->next && ((t_tag *)(tmp->next->content))->tag >= 0)
			{
				prev = tmp;
				(tmp) = (tmp)->next;
				prev->next = (tmp)->next;
				ft_lstdelone(tmp, free);
				tmp = prev;
			}
		}
		else
			*command_list = (*command_list)->next;
		tmp = (tmp)->next;
	}
	*command_list = start;
	return (0);
}