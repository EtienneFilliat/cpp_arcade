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

LDFLAGS		+=	-lcriterion

NAME	=	arcade

NAME_T	=	unit_test

MAINSRC	=	src/Main.cpp

MAINOBJ	=	$(MAINSRC:.cpp=.o)

SRCS	=	src/Core.cpp		\
		src/Exception.cpp	\

SRCS_T	=	tests/Exception.cpp	\

OBJS	=	$(SRCS:.cpp=.o)

OBJS_T	=	$(SRCS_T:.cpp=.o)

all:			$(NAME)

test:			$(NAME_T)

$(NAME):		$(OBJS) $(MAINOBJ)
			$(CXX) $(OBJS) $(MAINOBJ) -ldl -o $(NAME)

$(NAME_T):		$(OBJS) $(OBJS_T)
			$(CXX) $(OBJS) $(OBJS_T) -o $(NAME_T) $(LDFLAGS)

clean:
		$(RM) $(OBJS)
		$(RM) $(OBJS_T)
		$(RM) $(MAINOBJ)

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(NAME_T)

re:		fclean all

.PHONY:		all test clean fclean re



