NAME    =   minishell

CC      =   gcc 
CFLAGS  =   -Wall -Wextra -Werror
DIR_LIB =	printf/
HEADER  =   includes

LFLAGS  =   -I $(HEADER)

SRCS    =	srcs/minishell.c srcs/commande.c srcs/get_pwd.c\
			srcs/parsing.c srcs/utils.c srcs/utils2.c srcs/utils_parsing.c \
			srcs/dir_function.c srcs/env_function.c srcs/commande_line.c srcs/echo_function.c srcs/execve_function.c

OBJ     =   $(SRCS:.c=.o)

all: lib $(NAME)

lib:
	@make -C $(DIR_LIB)

%.o : %.c $(HEADER)/minishell.h
	@echo "\033[0;32m[OK] \033[0m \033[0;33m Compiling:\033[0m" $<
	@$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(DIR_LIB)libftprintf.a
	@echo "\033[0;32m[UPDATE] \033[0m \033[1;30m CREATED:\033[0m \033 \033[0m \033[0;36m minishell\033[0m"
	@gcc -g3 -fsanitize=address -o $(NAME)  $(OBJ) $(DIR_LIB)libftprintf.a

clean:
	@rm -f $(OBJ)
	@make clean -C $(DIR_LIB)
	@echo "\033[0;32m[UPDATE] \033[0m \033[1;30m REMOVED:\033[0m \033 \033[0m \033[3;31m *.o\033[0m \033"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(DIR_LIB)
	@echo "\033[0;32m[UPDATE] \033[0m \033[1;30m REMOVED:\033[0m \033 \033[0m \033[3;31m minishell\033[0m \033"

re : fclean all

.PHONY : all clean fclean remake
