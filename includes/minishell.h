/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 17:02:23 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 17:45:40 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../printf/fdprintf/includes/ft_printffd.h"
# include "../printf/includes/ft_printf.h"
# include "../printf/fdprintf/libft/include/libft.h"
# include "../printf/fdprintf/libft/include/get_next_line.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>

int			analyse(char *line, t_list *env);
int			exec_command(t_list *env, t_list *command_list);
char		*ft_append(char *dst, char *src, int size);
int			catch_command2(char *line, int *i, char *c, t_tag **command);
int			catch_command4(char *line, int *i, t_tag **command);
char		*ft_get_pwd(void);
int			cd_command(t_list *command_list, t_list *env);
int			call_command(t_list *command_list, t_list *env);
t_list		*envtab_to_envlst(char **envp);
int			unset_command(t_list *command_list, t_list *env);
int			reconfig_command(t_list **command_list, t_list *env, int nb);
char		*append_line(t_list **command_list, t_list *env);
int			echo_command(t_list *command_list, int fd, t_list *env);
int			execve_command(t_list *command_list, t_list *env, char *cmd);
int			ft_lstsize_nospace(t_list *lst);
int 		check_setvar(t_list *list);
int			preset_var(t_list *list, t_list *env);
char		**ft_lst_to_char(t_list *env);
#endif
