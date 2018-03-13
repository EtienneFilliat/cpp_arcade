##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
## Makefile for libsfml.so
##

CXX	=	g++

RM	=	rm -rf

CXXFLAGS	+=	-W -Wall -Wextra -Werror
CXXFLAGS	+=	-I../../include/
CXXFLAGS	+=	-std=c++11

NAME		=	bla

SRCS		=	main.cpp	\
			LibSfml.cpp

OBJS		=	$(SRCS:.cpp=.o)

LDFLAGS		=	-lsfml-graphics -lsfml-window -lsfml-system

all:	$(NAME)

$(NAME):		$(OBJS)
			$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
