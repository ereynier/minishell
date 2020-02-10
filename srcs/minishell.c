/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 17:02:36 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 17:44:13 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	while_command(char *line, char *path, t_list *env)
{
	int		err;
	char	*cp;

	if ((err = analyse(line, env)))
		ft_printf("Command syntax error\n");
	cp = ft_get_pwd();
	if (!(path = ft_strdup(ft_strrchr(cp, 47))))
		return (1);
	free(cp);
	path[2] == '\0' ? path = ft_strjoin(path, "~") : 0;
	err == 0 ? ft_printf("\033[1;32m➜  ") : ft_printf("\033[1;31m➜  ");
	ft_printf("\033[1;36m%s \033[1;33m✗ \033[0m", &path[1]);
	free(path);
	free(line);
	line = NULL;
	return (0);
}

static int	get_command(t_list *env)
{
	char	*line;
	char	*cp;
	char	*path;

	line = NULL;
	cp = ft_get_pwd();
	if (!(path = ft_strdup(ft_strrchr(cp, 47))))
		return (1);
	free(cp);
	path[2] == '\0' ? path = ft_strjoin(path, "~") : 0;
	if (ft_printf("\033[1;32m➜  \033[1;36m%s \033[1;33m✗ \033[0m",
	&path[1]) == -1)
		return (1);
	free(path);
	while (get_next_line(0, &line) > 0)
		if ((while_command(line, path, env)))
			return (1);
	line != NULL ? free(line) : 0;
	return (0);
}

int			main(int ac, char **av, char **envp)
{
	t_list *env;

	(void)ac;
	(void)av;
	if (!(env = envtab_to_envlst(envp)))
		return (1);
	ft_printf("\033[1;32mWELLCOME TO MINISHELL\033[0m\n");
	if (get_command(env))
		return (1);
	return (0);
}
