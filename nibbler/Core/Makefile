##
## Makefile for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
##
## Made by chanh allaux
## Login   <allaux_c@epitech.net>
##
## Started on  Tue Mar  8 12:56:53 2011 chanh allaux
## Last update Sun Mar 20 16:21:43 2011 romain tholimet
##

NAME			=	nibbler

SRCS			=	main.cpp		\
				Grid.cpp		\
				MinesweeperCore.cpp	\
				Option.cpp		\
				Core.cpp		\
				ACore.cpp		\
				CoreSound.cpp		\
				CoreFood.cpp		\
				CoreSpeed.cpp		\
				CoreTail.cpp		\
				CoreHead.cpp		\
				CoreSpecialMove.cpp	\
				CoreSprite.cpp		\
				CoreBest.cpp		\
				CoreSnake.cpp		\
				Parser.cpp

OBJS			=	$(SRCS:.cpp=.o)

LDXFLAGS		=	-ldl -lfmodex -lX11

CXFLAGS			+=	-W -Wall -Wextra

CXX			=	g++

RM			=	rm -f

$(NAME)			:	$(OBJS)
			$(CXX) -o $(NAME) $(OBJS) -export-dynamic $(CXFLAGS) $(LDXFLAGS)

all			:	$(NAME)

clean			:
			$(RM) $(OBJS)

fclean			:	clean
			$(RM) $(NAME)

re			:	fclean all

.PHONY			:	all clean fclean re
