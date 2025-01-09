##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

SRC	= 	src/set_client.c 						\
      	src/error_handling.c					\
      	src/connect_to_server.c					\
      	src/client_loop.c						\
      	src/redirect_fct/channel_fct.c			\
      	src/redirect_fct/error_fct.c			\
      	src/redirect_fct/error_unknown_fct.c	\
      	src/redirect_fct/help.c					\
      	src/redirect_fct/teams_fct.c			\
      	src/redirect_fct/thread_fct.c			\
      	src/redirect_fct/user_fct.c				\
      	src/redirect_fct/user_message_fct.c		\
		src/redirect_fct/info_fct.c				\
		src/redirect_fct/create_fct.c

MAIN =	src/main.c

INCLUDE =	include/		\
			../libs/myteams/	\

NAME	=	myteams_cli

CFLAGS = $(INCLUDE:%=-I%) -Wall -Wextra -g

LDFLAGS = -luuid -L${CURDIR}/../libs/myteams/

LDFLAGS_PROD = -l:libmyteams.so -ldl

LDFLAGS_DEV = -l:libmyteams.so -Wl,-rpath=${CURDIR}/../libs/myteams/

OBJ	=	$(SRC:.c=.o)

OBM =	$(MAIN:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ) $(OBM)
	@ gcc -o $(NAME) $(OBJ) $(OBM) $(LDFLAGS) $(LDFLAGS_PROD)
	@ cp $(NAME) ../

clean:
	rm -f $(OBJ) $(OBM)

fclean:	clean
	rm -f ../$(NAME)
	rm -f $(NAME)

re: fclean all

dev:	$(OBJ) $(OBM)
	@ gcc -o $(NAME) $(OBJ) $(OBM) $(LDFLAGS) $(LDFLAGS_DEV)
	@ cp $(NAME) ../

redev: fclean dev

.SILENT:

.PHONY: all clean fclean re
