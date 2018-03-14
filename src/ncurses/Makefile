##
## EPITECH PROJECT, 2018
## NAME_OF_PROJECT
## File description:
## This is a description kek
##

CXX		=	g++

CXXFLAGS	=	-W -Wall -Werror -Wextra -I ../../include/ -shared -fPIC

LDFLAGS		=	-lncurses

SRC		=	LibNcurses.cpp		\
			../Exception.cpp	\

OBJ		=	$(SRC:.cpp=.o)

NAME		=	libarcadencurces.so

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
