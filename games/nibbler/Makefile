##
## EPITECH PROJECT, 2018
## NAME_OF_PROJECT
## File description:
## This is a description kek
##

CXX	=	g++

RM	=	rm -rf

CXXFLAGS	=	-W -Wall -Werror -Wextra -I ../../include -shared -fPIC

SRC	=	Nibbler.cpp	\

NAME	=	lib_arcade_nibbler.so

all:	$(NAME)

$(NAME):
	$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)

fclean:
	$(RM) $(NAME)

fsym:
	$(RM) ../$(NAME)

re:	fclean all

.PHONY:	all fclean re
