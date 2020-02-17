/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:02:23 by jacens            #+#    #+#             */
/*   Updated: 2020/02/17 13:53:01 by jacens           ###   ########lyon.fr   */
/*                                                                            */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>

int			analyse(char *line, t_list **env);
int			exec_command(t_list *env, t_list *command_list);
char		*ft_append(char *dst, char *src, int size);
int			catch_command2(char *line, int *i, char *c, t_tag **command);
int			catch_command4(char *line, int *i, t_tag **command);
char		*ft_get_pwd(void);
int			cd_command(t_list *command_list, t_list *env);
int			call_command(t_list **command_list, t_list **env);
t_list		**envtab_to_envlst(char **envp);
int			unset_command(t_list *command_list, t_list *env);
int			reconfig_command(t_list **command_list, t_list *env);
char		*append_line(t_list **command_list, t_list *env);
int			echo_command(t_list *command_list, int fd, t_list *env);
int			execve_command(t_list *command_list, t_list *env, char *cmd);
int			ft_lstsize_nospace(t_list *lst);
int			check_setvar(t_list *list, int print);
int			preset_var(t_list *list, t_list *env, int set);
char		**ft_lst_to_char(t_list *env);
int			check_line(t_list *list);
int			export_command(t_list *list, t_list *env);
int			check_env(t_list *list, t_list *env);
void		print_export(t_list *env);
char		**ft_sortup(char **lst);
int			check_pipe(char *line);
void		exit_command(t_list *list, t_list **command_list, t_list **env,
			unsigned char i);
int			ft_lst_env_pwd(t_list *lst, char *old);
int			ft_free_foo(char **foo, int j);
int			config_foo(char *tmp, t_list *lst, t_list *env);
void		handle_sigint(int sig);
void		chdir_home_cmd(t_list *command_list, t_list *env,
			char *cp, char *tmp);
int			fill_ret_env(t_list *env, int ret);
int			ft_err_chdir(int i, char *str, t_list *env, char *tmp);
int			command_cmp(t_list *list, t_list **command_list, t_list **env,
			char *com);
int			env_command(t_list *command_list, t_list *env);
int			pwd_command(t_list *command_list);
int			do_all_pipe(t_list *list, t_list **command_list, t_list **env,
			char *com);
int			next_command_pipe(t_list *list, t_list **command_list, t_list **env,
			char *com);
int			ft_verif_redir(t_list *list, t_list **command_list, t_list **env,
			char *com);
void		ft_signal(int i);
int			catch_command_norme(char *line, int *i, char *c, t_tag **command);
int			call_command_norme(t_list **list, t_list ***command_list,
			t_list ***env, char **com);
int			ft_check_redir(t_list **command_list);
int			ft_count_nb_redir(t_list *tmp);
int			ft_count_nb_redir2(t_list *tmp);
int			ft_remove_all_multi_dir(int i, t_list *tmp);
int			ft_remove_all_multi_dir2(int i, t_list *tmp);
void		ft_change_order_list(t_list *lst);
int			ft_remove_all_multi_dirbis(int i, t_list *tmp);
int			ft_remove_all_multi_dir2bis(int i, t_list *tmp);
void		ft_reset_redir(int in, int out);
int			ft_change_dup_read(t_list *lst);
int			ft_change_dup_write(t_list *lst);
void		ft_remove_start_dir(t_list **lst);
void		ft_change_order_more(t_list *sp, t_list *redir,
			t_list *redirsp, t_list *file);
#endif
