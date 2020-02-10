/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env_function.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/11 06:29:53 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 16:45:20 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_list	*ft_unset(char *str, t_list *env)
{
	t_list *tmp;
	t_list *pre;

	tmp = env;
	pre = env;
	while (tmp)
	{
		if (!ft_strcmp(((t_tag *)(tmp->content))->str, str))
		{
			if (env == tmp)
				env = env->next;
			else
				pre->next = tmp->next;
			ft_lstdelone(tmp, free);
			break ;
		}
		pre = tmp;
		tmp = tmp->next;
	}
	return (env);
}

int				unset_command(t_list *command_list, t_list *env)
{
	char *str;

	while (1)
	{
		if (!(str = malloc(1)))
			return (1);
		str[0] = 0;
		while (command_list && (((t_tag *)(command_list->content))->tag == -32))
			command_list = command_list->next;
		if (!command_list || ((t_tag *)(command_list->content))->tag < 0)
			break ;
		str = append_line(&command_list, env);
		env = ft_unset(str, env);
		free(str);
	}
	free(str);
	return (0);
}

int				preset_var(t_list *list, t_list *env)
{
	int i;
	t_tag *new;
	char *str;

	i = 0;
	if (!(new = malloc(sizeof(t_tag))))
		return (1);
	if (!(str = malloc(1)))
		return (0);
	str[0] = 0;
	while (((t_tag *)(list->content))->str[i] != '=')
		i++;
	str = ft_append(str, ((t_tag *)(list->content))->str, i);
	i++;
	new->value = ft_strdup(&((t_tag *)(list->content))->str[i]);
	new->str = str;
	new->tag = 0;
	ft_lstadd_back(&env, ft_lstnew(new));
	return (1);
}