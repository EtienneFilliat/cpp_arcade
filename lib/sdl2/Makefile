##
## EPITECH PROJECT, 2018
## NAME_OF_PROJECT
## File description:
## This is a description kek
##

CXX		=	g++

RM	=	rm -rf

CXXFLAGS	=	-W -Wall -Werror -Wextra -I ../../include/ -shared -fPIC

LDFLAGS		=	-lSDL2 -lSDL2_ttf -lSDL2_image

SRC		=	LibSdl2.cpp		\
			../../src/Exception.cpp	\

NAME		=	lib_arcade_sdl2.so

all:	$(NAME)

$(NAME):
		$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME) $(LDFLAGS)

fclean:
	$(RM) $(NAME)

fsym:
	$(RM) ../../$(NAME)
	$(RM) ../$(NAME)

re:	fclean all

.PHONY:	all fclean re
