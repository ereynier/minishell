/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:40:00 by ereynier          #+#    #+#             */
/*   Updated: 2020/02/24 12:31:40 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			check_setvar(t_list *list, int print, int i)
{
	if (((t_tag *)(list->content))->str[i] == '=')
		return (0);
	while (ft_isalpha(((t_tag *)(list->content))->str[i]) ||
		((t_tag *)(list->content))->str[i] == '=')
	{
		if (((t_tag *)(list->content))->str[i] != '=')
			i++;
		else
			return (1);
	}
	if ((print == 2 && !((t_tag *)(list->content))->str[i]))
		return (1);
	if (print && !ft_isalpha(((t_tag *)(list->content))->str[i]) &&
		((t_tag *)(list->content))->str[i] != 0)
	{
		ft_printf("\033[1;31mminishell\033[0m: export: `");
		i = 0;
		while (((t_tag *)(list->content))->str[i] &&
		((t_tag *)(list->content))->str[i] != '=')
			ft_putchar(((t_tag *)(list->content))->str[i++]);
		ft_printf("': not a valid identifier\n");
	}
	return (0);
}

int			ft_lstsize_nospace(t_list *lst)
{
	int i;

	i = 1;
	while (lst && (((t_tag *)(lst->content))->tag >= 0 ||
	((t_tag *)(lst->content))->tag == -32))
	{
		if (lst && ((t_tag *)(lst->content))->tag == -32)
			lst = skip_redir_go_next(lst);
		if (lst && ((t_tag *)(lst->content))->tag >= 0)
		{
			i++;
			lst = skip_redir_go_next(lst);
		}
	}
	return (i);
}

static int	envtab_to_envlst2(t_tag **tag)
{
	if (!(*tag = malloc(sizeof(t_tag))))
		return (1);
	if (!((*tag)->str = malloc(1)))
	{
		free(*tag);
		return (1);
	}
	(*tag)->str[0] = 0;
	return (0);
}

t_list		**envtab_to_envlst(char **envp)
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
	return (env);
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
	free(dst);
	return (tmp);
}
