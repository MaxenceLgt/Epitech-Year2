##
## EPITECH PROJECT, 2024
## B-PDG-300-REN-3-1-PDGD04am-maxence.largeot
## File description:
## Makefile
##

SRC	=	src/main.cpp							\
		src/circuit/Circuit.cpp					\
		src/component/Clock.cpp					\
		src/component/False.cpp					\
		src/component/True.cpp					\
		src/component/Nand.cpp					\
		src/component/Output.cpp				\
		src/component/Input.cpp					\
		src/factory/ComponentFactory.cpp		\
		src/abstract/AComponent.cpp				\
		src/parsing/parsing.cpp					\
		src/shell/Shell.cpp

INCLUDE =	src/circuit/		\
			src/component/		\
			src/factory/		\
			src/abstract		\
			src/parsing			\
			src/shell


NAME	=	nanotekspice

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