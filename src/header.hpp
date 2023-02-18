#pragma once

# include <iostream>
# include <sys/socket.h>
# include <stdio.h>
# include <string.h>  
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>   
# include <arpa/inet.h>    
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/time.h>
# include <cstring>
# include "server/Server.hpp"
# include <exception>

#define ARGS_ERR "Usage: ./ircserv <port> <password>\nport: A number between 1025 and 65536\npassword: a sequence of characeters"
#define INVALID_ARGS() std::cerr << ARGS_ERR << std::endl
