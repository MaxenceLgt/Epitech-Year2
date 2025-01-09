##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

SRC	=	src/error_handling/display_usage.c		\
		src/error_handling/handle_err.c			\
		\
		src/server/server.c						\
		src/server/server_loop.c				\
		src/server/connection_handler.c			\
		\
		src/destroyers/destroy_server.c			\
		\
		src/cmd_handling/cmd_handler.c			\
		src/cmd_handling/cmd_parser.c			\
		src/cmd_handling/queue_handler.c		\
		src/cmd_handling/array_handler.c		\
		src/cmd_handling/padding_remover.c		\
		src/cmd_handling/parser_handler.c		\
		src/cmd_handling/subscribed.c			\
		src/cmd_handling/cmd_list_manager.c		\
		src/cmd_handling/login.c				\
		src/cmd_handling/logout.c				\
		src/cmd_handling/cmd_user.c				\
		src/cmd_handling/cmd_users.c			\
		src/cmd_handling/cmd_send.c				\
		src/cmd_handling/cmd_message.c			\
		src/cmd_handling/cmd_use.c				\
		src/cmd_handling/cmd_infos.c			\
		src/cmd_handling/subscribe.c			\
		src/cmd_handling/unsubscribe.c			\
		src/cmd_handling/create.c				\
		src/cmd_handling/create_team.c			\
		src/cmd_handling/create_channel.c		\
		src/cmd_handling/create_thread.c		\
		src/cmd_handling/create_reply.c			\
		\
		src/reply/invalid_reply.c				\
		src/reply/notify.c						\
		\
		src/getter/get_client.c					\
		src/getter/get_channel.c				\
		src/getter/get_team.c					\
		src/getter/get_threads.c				\
		src/getter/get_conv.c					\
		\
		src/load/load.c							\
		src/load/load_client.c					\
		src/load/load_client_conv.c				\
		src/load/load_client_message.c			\
		src/load/load_team.c					\
		src/load/load_client_team.c				\
		src/load/load_channel.c					\
		src/load/load_threads.c					\
		src/load/load_team_message.c			\
		src/load/my_str_to_word_array.c			\
		\
		src/save/save.c							\
		src/save/save_client.c					\
		src/save/save_client_conv.c				\
		src/save/save_client_message.c			\
		src/save/save_team.c					\
		src/save/save_client_team.c				\
		src/save/save_channel.c					\
		src/save/save_thread.c					\
		src/save/save_team_message.c

MAIN =	src/main.c

INCLUDE =	include						\
			include/server_struct		\
			KiweakLib/ml_headers/		\
			../libs/myteams/

NAME	=	myteams_server

CFLAGS = $(INCLUDE:%=-I%) -Wall -Wextra -g

LDFLAGS = 	-LKiweakLib/ -L${CURDIR}/../libs/myteams/ 	\
			-lml_lib -luuid
LDFLAGS_PROD = -l:libmyteams.so

LDFLAGS_DEV = -l:libmyteams.so -Wl,-rpath=${CURDIR}/../libs/myteams/

OBJ	=	$(SRC:.c=.o)

OBM =	$(MAIN:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ) $(OBM)
	@ make -C KiweakLib/
	@ gcc -o $(NAME) $(OBJ) $(OBM) $(LDFLAGS) $(LDFLAGS_PROD)
	@ cp $(NAME) ../

clean:
	@ make clean -C KiweakLib/
	@ rm -f $(OBJ) $(OBM)

fclean:	clean
	@ make fclean -C KiweakLib/
	@ rm -f ../$(NAME)
	@ rm -f $(NAME)

re: fclean all

dev:	$(OBJ) $(OBM)
	@ make -C KiweakLib/
	@ gcc -o $(NAME) $(OBJ) $(OBM) $(LDFLAGS) $(LDFLAGS_DEV)
	@ cp $(NAME) ../

redev: fclean dev

.SILENT:

.PHONY: all clean fclean re dev redev
