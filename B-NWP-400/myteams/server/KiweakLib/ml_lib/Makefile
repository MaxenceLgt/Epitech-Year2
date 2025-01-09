##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

SRC	=	src/list_managing/ml_create_list.c			\
		src/list_managing/ml_add_node_back.c		\
		src/list_managing/ml_add_node_front.c		\
		src/list_managing/ml_display_list.c			\
		src/list_managing/ml_destroy_node.c			\
		src/list_managing/ml_destroy_list.c

INCLUDE = include/

NAME	=	libml_lib.a

CFLAGS = $(INCLUDE:%=-I%) -Wall -Wextra

OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc -o ../$(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re: fclean all

.SILENT:
