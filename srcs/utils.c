/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/03 14:40:00 by ereynier     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 14:47:58 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int 		check_setvar(t_list *list)
{
	int i;
	
	i = 0;
	while (((t_tag *)(list->content))->str[i])
	{
		if (((t_tag *)(list->content))->str[i] != '=')
			i++;
		else
			return (1);
	}
	return (0);
}

int			ft_lstsize_nospace(t_list *lst)
{
	int i;

	i = 1;
	while (lst && ((t_tag *)(lst->content))->tag != -59)
	{
		if (lst && ((t_tag *)(lst->content))->tag == -32)
			lst = lst->next;
		if (lst && ((t_tag *)(lst->content))->tag != -59)
		{
			i++;
			lst = lst->next;
		}
	}
	return (i);
}

static int	envtab_to_envlst2(t_tag **tag)
{
	if (!(*tag = malloc(sizeof(t_tag))))
		return (1);
	if (!((*tag)->str = malloc(1)))
		return (1);
	(*tag)->str[0] = 0;
	if (!((*tag)->value = malloc(1)))
		return (1);
	(*tag)->value[0] = 0;
	return (0);
}

t_list		*envtab_to_envlst(char **envp)
{
	t_list	**env;
	t_tag	*tag;
	int		i;
	int		j;

	i = -1;
	tag = 0;
	env = malloc(sizeof(t_list*));
	*env = 0;
	while (envp[++i])
	{
		if (envtab_to_envlst2(&tag))
			return (NULL);
		j = 0;
		while (envp[i][j] != '=')
			j++;
		tag->str = ft_append(tag->str, envp[i], j);
		j++;
		tag->value = ft_strdup(&envp[i][j]);
		tag->tag = 1;
		ft_lstadd_back(env, ft_lstnew(tag));
	}
	return (*env);
}

char		*ft_append(char *dst, char *src, int size)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = ft_strlen(dst);
	if (!(tmp = malloc(i + size + 2)))
		return (0);
	i = 0;
	while (dst[i])
	{
		tmp[i] = dst[i];
		i++;
	}
	while (j < size)
	{
		tmp[i + j] = src[j];
		j++;
	}
	tmp[i + j] = 0;
	return (tmp);
}
