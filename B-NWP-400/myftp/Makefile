##
## EPITECH PROJECT, 2023
## Untitled (Workspace)
## File description:
## Makefile
##

SRC =	src/main.c					\
		src/server/client_list.c	\
		src/server/server.c			\
		src/server/fd_sets.c		\
		src/commands/command_spliter.c	\
		src/commands/handle_command.c	\
		src/commands/error_codes_cmd.c	\
		src/commands/user_commands.c	\
		src/commands/simple_commands.c	\
		src/commands/pasv_actif_commands.c	\
		src/commands/path_commands.c	\
		src/commands/file_commands.c	\
		src/commands/list.c				\
		src/commands/retrieve.c			\
		src/commands/stor.c				\
		src/errorHandling/argument_errors.c

INCLUDE =	include/

CFLAGS = $(INCLUDE:%=-I%) -Wall -Wextra -D_GNU_SOURCE

NAME	=	myftp

OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	rm -f *.gcno
	rm -f *.gcda

re: fclean all

.PHONY: all clean fclean re
