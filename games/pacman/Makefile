##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
## Pacman
##

CXX		=	g++

RM		=	rm -rf

CXXFLAGS	=	-W -Wall -Wextra -I ../../include/ #-shared -fPIC

SRC		=	main.cpp		\
			Pacman.cpp		\
			../../src/Exception.cpp	\

#NAME		=	lib_arcade_pacman.so

NAME		=	pacman

all:	$(NAME)

$(NAME):
	$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)

fclean:
	$(RM) $(NAME)

fsym:
	$(RM) ../../$(NAME)

re:	fclean all

.PHONY:	all clean fclean re
