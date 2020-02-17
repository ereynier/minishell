/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_foo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:03:12 by jacens            #+#    #+#             */
/*   Updated: 2020/02/16 19:54:22 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_change_value_str(t_list *lst, t_list *env, char **foo)
{
	char	*tmp;

	while (((t_tag *)(env->content)) &&
	ft_strncmp(((t_tag *)(env->content))->str, "HOME", 5) != 0)
		env = env->next;
	if (!(tmp = ft_strjoin(((t_tag *)(env->content))->value,
	&((t_tag *)(lst->content))->str[1])))
		return (ft_free_foo(foo, 1));
	free(((t_tag *)(lst->content))->str);
	((t_tag *)(lst->content))->str = tmp;
	return (1);
}

static char	**ft_lst_to_foo(char **foo, char *tmp, t_list *lst, t_list *env)
{
	int		i;
	int		j;

	j = ft_lstsize_nospace(lst) + 1;
	if (!(foo = malloc(j)))
		return (NULL);
	i = j;
	while (--i > 0)
		foo[i] = NULL;
	foo[i] = tmp;
	while (++i < j - 1)
	{
		lst = lst->next;
		if (!strncmp(((t_tag *)(lst->content))->str, "~", 1) &&
		!((t_tag *)(lst->content))->tag)
			if (!ft_change_value_str(lst, env, foo))
				return (NULL);
		foo[i] = ((t_tag *)(lst->content))->str;
		lst = lst->next;
	}
	foo[i] = NULL;
	return (foo);
}

int			config_foo(char *tmp, t_list *lst, t_list *env)
{
	char	**foo;
	char	**envp;
	int		ret;

	foo = NULL;
	if (!(envp = ft_lst_to_char(env)))
		return (0);
	if (!(foo = ft_lst_to_foo(foo, tmp, lst, env)))
		return (ft_free_foo(envp, 2));
	ret = execve(foo[0], foo, envp);
	if (ret == -1)
	{
		ft_printf_fd(2, "\033[1;31mminishell\033[0m: %s %s\n",
		"no such file or directory:", foo[0]);
		ft_free_foo(envp, 2);
		return (ft_free_foo(foo, 1));
	}
	ft_free_foo(foo, 1);
	return (ft_free_foo(envp, 2) + 1);
}
