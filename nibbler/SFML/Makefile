##
## Makefile for nibbler in /home/tholim_r//nibbler-2014-benram_s/SFML
##
## Made by romain tholimet
## Login   <tholim_r@epitech.net>
##
## Started on  Sat Mar 12 16:19:25 2011 romain tholimet
## Last update Sun Mar 20 15:22:57 2011 romain tholimet
##

NAME	=	lib_nibbler_SFML.so

CXX	=	g++

INCLUDE	=	-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

CXXFLAGS +=	-Wall -Wextra -Werror $(INCLUDE)

LDFLAGS	+=	-I../Core/ $(INCLUDE) -shared -fPIC

SRC	=	LibrarySFML.cpp

OBJ	=	$(SRC:.cpp=.o)

RM	=	rm -f

.cpp.o:
		$(CXX) $(CXXFLAG) -c $< -o $@ $(LDFLAGS)

$(NAME)	:	$(OBJ)
		$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all	:	$(NAME)

re	:	fclean all

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

.PHONY	:	all re clean fclean