##
## EPITECH PROJECT, 2019
## minishell1
## File description:
## Makefile
##

SRC		=	src/my_malloc.c		\
			src/alloc.c			\
			src/complement.c	\

TEST	=	src/my_malloc.c		\
			src/alloc.c			\
			src/complement.c	\
			tests/unit_tests.c	

OBJ		=	$(SRC:.c=.o)

CC		=	gcc -shared -I./include -fPIC -ggdb

CCTEST 	= 	gcc -D DEBUG -I./include

NAME	=	libmy_malloc.so

CPP_FLAGS	=	-W -Wall -Werror -Wextra -std=c++11

all:	$(NAME)


$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(CPP_FLAGS) $(OBJ)
	make tests_run

tests_run:	$(TEST)
	$(CCTEST) -o unit_tests $(TEST) -lcriterion --coverage -D DEBUG
	./unit_tests | gcovr
	make clean

clean:
	rm -f $(shell find $(SOURCEDIR) -name '*.o')
	rm -f $(shell find $(SOURCEDIR) -name '*~')
	rm -f $(shell find $(SOURCEDIR) -name '*#')
	rm -f $(shell find $(SOURCEDIR) -name '*vg*')
	rm -f $(shell find $(SOURCEDIR) -name '*.gc*')


fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all tests_run clean fclean re
