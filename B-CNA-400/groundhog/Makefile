##
## EPITECH PROJECT, 2024
## B-CNA-410-REN-4-1-groundhog-maxence.largeot
## File description:
## Makefile
##

SRC	=	src/main.cpp	\
		src/day.cpp		\
		src/parseur.cpp

INCLUDE =	src/day/		\
			src/parseur/		

NAME	=	groundhog

CPPFLAGS = $(INCLUDE:%=-I%) -std=c++20 -Wall -Wextra -Werror

CPPFLAGSTEST = -lcriterion --coverage

OBJ	=	$(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	rm -f *.gcno
	rm -f *.gcda

re: fclean all

tests_run:
	g++ -o unit_tests $(filter-out src/main.cpp, $(SRC)) \
	tests/unit_tests.cpp -I include/ $(CPPFLAGSTEST) $(CPPFLAGS)
	-./unit_tests

.PHONY: all clean fclean re