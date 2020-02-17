/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:05:15 by jacens            #+#    #+#             */
/*   Updated: 2020/02/14 11:41:24 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <strings.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <unistd.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_tag
{
	char			*str;
	int				tag;
	char			*value;
}					t_tag;

void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_listadd_front(t_list **alst, t_list *new);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_base(int nbr, char *base);
void				ft_putstr(char *str);
void				ft_putchar(char c);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlen(char const *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
int					ft_atoi(const char *str);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_check_base(char *base);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					check_base(char *base);
int					ft_atoi_base(char *str, char *base);
int					ft_count_nbr(long long n);
int					ft_count_nbr_base(long long n, int len);
int					ft_lstsize(t_list *lst);
char				*ft_strchr(const char *s, int c);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strdup(const char *src);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strstr(const char *haystack, const char *to_find);
char				*ft_strnstr(const char *haystack, const char *needle,\
					size_t len);
char				*ft_itoa_base(long n, char *base);
char				*ft_uitoa_base(void *n, char *base);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strrchr(const char *s, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_create_base(int size);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),\
					void (*del)(void *));
char				*ft_uitoa(unsigned int n);
int					ft_strcount_char(char *str, char find);
int					ft_iswspace(char c);

#endif
