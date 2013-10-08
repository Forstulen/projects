##
## Makefile for plazza in /home/benram_s//Desktop/program/cpp/plazza-2014-tholim_r
##
## Made by soufien benramdhane
## Login   <benram_s@epitech.net>
##
## Started on  Thu Apr  7 11:59:58 2011 soufien benramdhane
## Last update Sun Apr 17 23:00:22 2011 chanh allaux
##

NAME		=		plazza

RM		=		rm -f

SOURCE_DIR	=		./sources/

ACCESS		=		$(SOURCE_DIR)access/

INTERFACE	=		$(SOURCE_DIR)interfaces/

PLAZZA		=		$(SOURCE_DIR)plazza/

NAMEPIPE	=		$(SOURCE_DIR)namedpipe/

EXCEPTION	=		$(SOURCE_DIR)exception/

SOURCE		=		main.cpp 			\
				$(PLAZZA)Pizza.cpp 		\
				$(PLAZZA)Kitchen.cpp		\
				$(PLAZZA)Stock.cpp		\
				$(PLAZZA)Cook.cpp		\
				$(PLAZZA)Serializer.cpp 	\
				$(PLAZZA)Reception.cpp	 	\
				$(SOURCE_DIR)Fork.cpp	 	\
				$(ACCESS)Mutex.cpp 		\
				$(ACCESS)Thread.cpp 		\
				$(SOURCE_DIR)Waiter.cpp		\
				$(NAMEPIPE)NamedPipe.cpp 	\
				$(EXCEPTION)systemError.cpp

OBJ		=		$(SOURCE:.cpp=.o)

INCLUDE		=		-I$(SOURCE_DIR) -I$(PLAZZA) -I$(INTERFACE) -I$(ACCESS) -I$(NAMEPIPE) -I$(EXCEPTION) -I$(PARSER)

CXXFLAGS	+=		-W -Wall -Wextra $(INCLUDE) -export-dynamic

LDFLAGS		+=		-lpthread -lrt -ldl

$(NAME)		:		$(OBJ)
				g++ -o $(NAME) $(OBJ) $(LDFLAGS)

all_lib		:		$(NAME)
				cd lib_plazza_Qt/ ; qmake-qt4 ; make

all		:		$(NAME)
				@cd lib_plazza_Qt ; make ; cd -
clean		:
				$(RM) $(OBJ)

fclean		:		clean
				$(RM) $(NAME)
				@cd lib_plazza_Qt ; make clean ; cd -

re		:		fclean all

.PHONY		:		all clean fclean re