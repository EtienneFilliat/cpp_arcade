##
## EPITECH PROJECT, 2018
## NAME_OF_PROJECT
## File description:
## This is a description kek
##

CXX		=	g++

RM		=	rm -rf

CXXFLAGS	=	-W -Wall -Werror -Wextra -I ../../include/ -shared -fPIC

LDFLAGS		=	-lncurses

SRC		=	LibNcurses.cpp		\
			../../src/Exception.cpp	\

OBJ		=	$(SRC:.cpp=.o)

NAME		=	lib_arcade_ncurces.so

all:	$(NAME)

$(NAME):
	$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME) $(LDFLAGS)


fclean:
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
