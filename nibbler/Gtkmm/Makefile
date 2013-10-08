##
## Makefile for Makefile in /home/benram_s//Desktop/program/cpp/nibbler-2014-benram_s/Gtkmm
##
## Made by soufien benramdhane
## Login   <benram_s@epitech.net>
##
## Started on  Sat Mar 12 18:55:44 2011 soufien benramdhane
## Last update Sun Mar 20 15:38:02 2011 romain tholimet
##

NAME =		lib_nibbler_Gtkmm.so

CXX =		g++

INCLUDE	=	`pkg-config gtkmm-2.4 --cflags --libs`

CXXFLAGS +=	-Wall -Wextra -Werror $(INCLUDE)

LDFLAGS	+=	-I../Core/ $(INCLUDE) -shared -fPIC

SRC	=	gtkWindow.cpp		\
		libGtkmm.cpp

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
