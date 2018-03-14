##
## EPITECH PROJECT, 2018
## NAME_OF_PROJECT
## File description:
## This is a description kek
##

CXX		=	g++

RM	=	rm -rf

CXXFLAGS	=	-W -Wall -Werror -Wextra -I ../../include/ -shared -fPIC

LDFLAGS		=	-lcaca

SRC		=	Libcaca.cpp		\
			../../src/Exception.cpp	\

NAME		=	lib_arcade_libcaca.so

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME) $(LDFLAGS)

fclean:
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all fclean re
