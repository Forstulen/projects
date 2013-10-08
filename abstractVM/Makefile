##
## Makefile for make in /home/benram_s//Desktop/abstractvm-2014-tholim_r/abstractVM
## 
## Made by soufien benramdhane
## Login   <benram_s@epitech.net>
## 
## Started on  Thu Feb 17 14:33:34 2011 soufien benramdhane
## Last update Sun Feb 20 20:51:05 2011 soufien benramdhane
##

NAME		=		avm

RM		=		rm -f

SOURCE		=		create.cpp \
				Instruction.cpp \
				Machine.cpp \
				main.cpp \
				systemError.cpp

OBJ		=		$(SOURCE:.cpp=.o)

CXXFLAGS	+=		-W -Wall -Werror

$(NAME)		:		$(OBJ)
				$(CXX) -o $(NAME) $(SOURCE)

all		:		$(NAME)

clean		:
				$(RM) $(OBJ)

fclean		:		clean
				$(RM) $(NAME)

re		:		fclean all

.PHONY		:		all clean fclean re