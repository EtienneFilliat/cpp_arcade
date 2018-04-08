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

CORE	=	arcade

NAME_T	=	unit_test

MAINSRC	=	src/Main.cpp

MAINOBJ	=	$(MAINSRC:.cpp=.o)

SRCS	=	src/Core.cpp		\
		src/Exception.cpp

SRCS_T	=	tests/Exception.cpp	\

OBJS	=	$(SRCS:.cpp=.o)

OBJS_T	=	$(SRCS_T:.cpp=.o)

ifndef VERBOSE
	MAKEFLAGS	+=	--no-print-directory
endif

all:		core graphicals games

core:		$(CORE)

graphicals:
		@$(MAKE) -C lib/libcaca/
		@mv lib/libcaca/*.so ./lib
		@$(MAKE) -C lib/sfml/
		@mv lib/sfml/*.so ./lib
		@$(MAKE) -C lib/ncurses
		@mv lib/ncurses/*.so ./lib
		@$(MAKE) -C lib/sdl2
		@mv lib/sdl2/*.so ./lib
		@ln -sf lib/*.so ./

games:
		@$(MAKE) -C games/nibbler/
		@mv games/nibbler/*.so ./games/
		@$(MAKE) -C games/pacman/
		@mv games/pacman/*.so ./games/

$(CORE):	$(OBJS) $(MAINOBJ)
		$(CXX) $(OBJS) $(MAINOBJ) -ldl -o $(CORE)


test:		$(NAME_T)

$(NAME_T):	$(OBJS) $(OBJS_T)
		$(CXX) $(OBJS) $(OBJS_T) -o $(NAME_T) $(LDFLAGS)

clean:
		$(RM) $(OBJS)
		$(RM) $(OBJS_T)
		$(RM) $(MAINOBJ)
		@$(MAKE) fclean fsym -C lib/libcaca/
		@$(MAKE) fclean fsym -C lib/sfml/
		@$(MAKE) fclean fsym -C lib/ncurses/
		@$(MAKE) fsym -C games/pacman/
		@$(MAKE) fsym -C games/nibbler/

fclean:		clean
		$(RM) $(CORE)
		$(RM) $(NAME_T)

re:		fclean all

.PHONY:		all test clean fclean re core graphicals games



