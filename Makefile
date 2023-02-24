NAME = ircserv

CPP = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = ./src/main.cpp ./src/server/server.cpp ./src/Commands/Commands.cpp ./src/client/client.cpp

INC = ./src/header.hpp ./src/server/server.hpp ./src/Commands/Commands.hpp ./src/client/client.hpp

OBJ = $(SRC:.cpp=.o)

%.o : %.cpp $(INC)
	@$(CPP) $(CPPFLAGS) -o $@  -c $<

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all