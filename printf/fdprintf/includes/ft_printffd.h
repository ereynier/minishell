/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printffd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:39:52 by jacens            #+#    #+#             */
/*   Updated: 2020/02/14 11:41:18 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTFFD_H
# define FT_PRINTFFD_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"

typedef struct		s_printfd
{
	int				space;
	int				zero;
	int				left;
	int				print;
	char			*arg;
	int				intnull;
	int				dot;
	int				fd;
}					t_printfd;

int					ft_printf_fd(int fd, const char *format, ...);
int					ft_no_pre_fd(const char *format, va_list *args,
								int *valprintf, t_printfd *struc);
int					ft_with_pre_fd(const char *format, va_list *args,
								int *valprintf, t_printfd *struc);
void				ft_end_one_check_fd(t_printfd *struc);
t_printfd			*ft_set_struct_fd(t_printfd *struc, int fd);
char				*ft_config_flags_fd(va_list *args, char format,
								int *valprintf, t_printfd *struc);
char				*ft_va_null_char_fd(va_list *args, t_printfd *struc);
int					ft_va_null_int_fd(va_list *args, t_printfd *struc);
void				ft_print_pre_fd(int *valprintf, t_printfd *struc,
								char *ptr, char format);
void				ft_print_zero_fd(int *valprintf, t_printfd *struc,
								char *ptr, char format);
void				ft_with_pre_do_fd(char format, int *valprintf, char *ptr,
								t_printfd *struc);
void				ft_do_more_config_fd(const char *format, va_list *args,
								t_printfd *struc, int i);
void				ft_more_config_struc_fd(t_printfd *struc, char format,
								char *ptr);
void				ft_more_config_struc2_fd(t_printfd *struc, char format,
								char *ptr);
void				ft_more_config_struc3_fd(t_printfd *struc, char format,
								char *ptr);
void				ft_print_space_fd(int *valprintf, t_printfd *struc);
void				ft_config_stru_fd(t_printfd *struc, char *ptr);
void				ft_config_stru2_fd(t_printfd *struc, char *ptr);
void				ft_config_stru3_fd(int *valprintf, t_printfd *struc,
								char *ptr, char format);
void				ft_config_stru4_fd(t_printfd *struc, char *ptr,
								int *valprintf, char format);
void				ft_cas_d_1_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_1_2_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_1_3_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_1bis_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_2_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_3_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_4_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_5_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_6_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_7_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_7_1_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_7_2_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_8_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_9_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_10_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_11_fd(t_printfd *struc, char *ptr,
								int *valprintf);
void				ft_cas_d_12_fd(t_printfd *struc, char *ptr);
void				ft_cas_d_13_fd(t_printfd *struc, char *ptr);

#endif
