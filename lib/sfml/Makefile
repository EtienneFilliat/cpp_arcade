##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
## Makefile for libsfml.so
##

CXX	=	g++

RM	=	rm -rf

CXXFLAGS	=	-W -Wall -Wextra -Werror	\
			-I../../include/		\
			-std=c++11			\
			-shared -fPIC

NAME		=	lib_arcade_sfml.so

SRC		=	LibSfml.cpp	\
			../../src/Exception.cpp

LDFLAGS		=	-lsfml-graphics -lsfml-window -lsfml-system

all:	$(NAME)

$(NAME):		$(OBJS)
			$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME) $(LDFLAGS)

fclean:
		$(RM) $(NAME)

fsym:
	$(RM) ../../$(NAME)

re:		fclean all

.PHONY:		all fclean re
