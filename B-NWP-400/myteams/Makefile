##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

all:
	make -C client/
	make -C server/

clean:
	make clean -C client/
	make clean -C server/

fclean:	clean
	make fclean -C client/
	make fclean -C server/

re: fclean all

dev:
	make dev -C client/
	make dev -C server/

redev:
	make redev -C client/
	make redev -C server/

.SILENT:

.PHONY: all clean fclean re
