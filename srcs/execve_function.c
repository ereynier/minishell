/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execve_function.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/07 15:45:52 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 18:02:25 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_free_foo(char **foo, int j)
{
	int i;

	i = -1;
	if (j == 1)
	{
		if (foo[0])
		{
			free(foo[0]);
			foo[0] = NULL;
		}
	}
	// else
	// 	while (foo[++i])
	// 	{
	// 		free(foo[i]);
	// 		foo[i] = NULL;
	// 	}
	free(foo);
	foo = NULL;
	return (0);
}

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

char		**ft_lst_to_foo(char **foo, char *tmp, t_list *lst, t_list *env)
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

static int	config_foo(char *tmp, t_list *lst, t_list *env)
{
	char	**foo;
	char	**envp;
	int		ret;

	foo = NULL;
	if (!(envp = ft_lst_to_char(env)))
		;
	if (!(foo = ft_lst_to_foo(foo, tmp, lst, env)))
		ft_free_foo(envp, 2);
	ret = execve(foo[0], foo, NULL);
	if (ret == -1)
	{
		ft_printf("\033[1;31mminishell\033[0m: %s %s\n",
		"no such file or directory:", foo[0]);
		ft_free_foo(envp, 2);
		return (ft_free_foo(foo, 1));
	}
	ft_free_foo(foo, 1);
	return (ft_free_foo(envp, 2) + 1);
}

int			execve_command(t_list *command_list, t_list *env, char *cmd)
{
	char	*tmp;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		tmp = (ft_strncmp(cmd, "/bin/", 5) != 0 ?
		ft_strjoin("/bin/", cmd) : ft_strdup(cmd));
		if (!(config_foo(tmp, command_list, env)))
			return (0);
	}
	else
		wait(&status);
	return (1);
}
