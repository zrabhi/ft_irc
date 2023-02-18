NAME = ircserv

CPP = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = ./src/main.cpp ./src/server/Server.cpp

INC = ./src/header.hpp ./src/server/Server.hpp

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