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
# include "./server/Server.hpp"
# include <exception>
# include <cstring>
# include <netinet/in.h>
# include <sys/_endian.h>
# include <sys/_types/_socklen_t.h>


#define ARGS_ERR "Usage: ./ircserv <port> <password>\nport: A number between 1025 and 65536\npassword: a sequence of characeters"
#define INVALID_ARGS() std::cerr << ARGS_ERR << std::endl
# define ERR_NONICKNAMEGIVEN std::cout << "Error(431):No nickname given" << std::endl;
#define  ERR_UNKNOWNCOMMAND(a)  std::cout << "Error(421):"  << a << " Unknown command"  << std::endl;