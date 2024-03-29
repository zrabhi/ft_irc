NAME = ircserv

CPP = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98  #-fsanitize=address 

SRC = ./src/main.cpp ./src/server/server.cpp ./src/Commands/NICK.cpp ./src/Commands/USER.cpp ./src/Commands/PASS.cpp \
		./src/Commands/PRIVMSG.cpp ./src/Commands/JOIN.cpp ./src/Commands/PART.cpp  ./src/Commands/QUIT.cpp \
		./src/Commands/KICK.cpp ./src/Commands/NOTICE.cpp ./src/Commands/Commands.cpp ./src/client/client.cpp\
			./src/Commands/TOPIC.cpp ./src/Commands/BOT.cpp ./src/Channel/channel.cpp 
		

INC = ./src/header.hpp ./src/server/server.hpp ./src/Commands/Commands.hpp ./src/client/client.hpp ./src/Channel/channel.hpp 
OBJ = $(SRC:.cpp=.o)

%.o : %.cpp $(INC)
	@$(CPP) $(CPPFLAGS) -o $@  -c $<

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CPP) $(CPPFLAGS) -lcurl $(OBJ) -o $(NAME)
	@echo server started
clean :
	@rm -rf $(OBJ)
fclean : clean
	@rm -rf $(NAME)
re : fclean all