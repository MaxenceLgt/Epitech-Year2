##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC =	strlen.asm	\
		strchr.asm	\
		strrchr.asm	\
		strcmp.asm	\
		strncmp.asm	\
		strcspn.asm	\
		strpbrk.asm	\
		strstr.asm	\
		strcasecmp.asm	\
		memset.asm	\
		memcpy.asm	\
		memmove.asm

TEST = tests/minilibC.c

UNAME = unit_tests

UFLAGS	= --coverage -lcriterion

GC = 	*.gcda	\
		*.gcno

OBJ	=	$(SRC:.asm=.o)

NAME	=	libasm.so

all:	$(NAME)

%.o: %.asm
	nasm -f elf64 $< -o $@

$(NAME):	$(OBJ)
	ld -shared -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -rf $(GC)

fclean:	clean
	rm -f $(NAME)
	rm -rf $(UNAME)

re: fclean all

tests_run:	$(NAME)
	@ gcc -o $(UNAME) $(TEST) $(UFLAGS) -ldl
	@ ./$(UNAME)
	@ gcovr --exclude /tests

.PHONY: all clean fclean re
