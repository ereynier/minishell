/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 14:39:52 by jacens       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 13:31:18 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "../fdprintf/libft/include/libft.h"
# include "../fdprintf/libft/include/get_next_line.h"

typedef struct		s_print
{
	int				space;
	int				zero;
	int				left;
	int				print;
	char			*arg;
	int				intnull;
	int				dot;
}					t_print;

int					ft_printf(const char *format, ...)
		 __attribute__((format(printf,1,2)));
int					ft_no_pre(const char *format, va_list *args,
								int *valprintf, t_print *struc);
int					ft_with_pre(const char *format, va_list *args,
								int *valprintf, t_print *struc);
void				ft_end_one_check(t_print *struc);
t_print				*ft_set_struct(t_print *struc);
char				*ft_config_flags(va_list *args, char format, int *valprintf,
								t_print *struc);
char				*ft_va_null_char(va_list *args, t_print *struc);
int					ft_va_null_int(va_list *args, t_print *struc);
void				ft_print_pre(int *valprintf, t_print *struc, char *ptr,
								char format);
void				ft_print_zero(int *valprintf, t_print *struc, char *ptr,
								char format);
void				ft_with_pre_do(char format, int *valprintf, char *ptr,
								t_print *struc);
void				ft_do_more_config(const char *format, va_list *args,
								t_print *struc, int i);
void				ft_more_config_struc(t_print *struc, char format,
								char *ptr);
void				ft_more_config_struc2(t_print *struc, char format,
								char *ptr);
void				ft_more_config_struc3(t_print *struc, char format,
								char *ptr);
void				ft_print_space(int *valprintf, t_print *struc);
void				ft_config_stru(t_print *struc, char *ptr);
void				ft_config_stru2(t_print *struc, char *ptr);
void				ft_config_stru3(int *valprintf, t_print *struc, char *ptr,
								char format);
void				ft_config_stru4(t_print *struc, char *ptr, int *valprintf,
								char format);
void				ft_cas_d_1(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_1_2(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_1_3(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_1bis(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_2(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_3(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_4(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_5(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_6(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_7(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_7_1(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_7_2(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_8(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_9(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_10(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_11(t_print *struc, char *ptr, int *valprintf);
void				ft_cas_d_12(t_print *struc, char *ptr);
void				ft_cas_d_13(t_print *struc, char *ptr);
#endif
