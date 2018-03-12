##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
## Makefile
##

CXX	=	g++

RM	=	rm -rf

CXXFLAGS	+=	-W -Wall -Wextra #-Werror
CXXFLAGS	+=	-Iinclude/
CXXFLAGS	+=	-std=c++11

NAME	=	arcade

MAINSRC	=	src/Main.cpp

MAINOBJ	=	$(MAINSRC:.cpp=.o)

SRC	=	src/Core.cpp

OBJS	=	$(SRC:.cpp=.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(MAINOBJ)
			$(CXX) $(OBJS) $(MAINOBJ) -o $(NAME)

clean:
		$(RM) $(OBJS)
		$(RM) $(MAINOBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re



