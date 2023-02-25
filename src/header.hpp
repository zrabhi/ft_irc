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
# include <fcntl.h>
# include <poll.h>
# include <vector>
# include <exception>
# include <cstring>
# include <netinet/in.h>
# include <sys/_endian.h>
# include <sys/_types/_socklen_t.h>
# include "./server/server.hpp"

enum T_flag
{   
    NOT_REGISTERED = 0,
    REGISTERD = 1,
};

# define   ARGS_ERR "Usage: ./ircserv <port> <password>\nport: A number between 1025 and 65536\npassword: a sequence of characeters"
# define   INVALID_ARGS() std::cerr << ARGS_ERR << std::endl
# define   ERR_NONICKNAMEGIVEN std::cout << "Error(431): No nickname given" << std::endl;
# define   ERR_UNKNOWNCOMMAND(a)  std::cout << "Error(421): "  << a << " Unknown command"  << std::endl;
# define   ERR_NEEDMOREPARAMS(a) std::cout << a << " :Not enough parameters" << std::endl;
# define   ERR_NICKNAMEINUSE(a) std::cout << a << " :Nickname is already in use" << std::endl;
# define   ERR_USERNOTINCHANNEL(a, b) std::cout << a << " :They aren't on that channel" << b << std::endl;
# define   ERR_NOTONCHANNEL(a) std::cout << a << " :You're not on that channel" << std::endl;
# define   ERR_USERONCHANNEL(a, b) std::cout << a << " " << b << " :is already on channel" << std::endl;
# define   ERR_SUMMONDISABLED(a)  std::cout << a << " has been disabled" << std::endl;
# define   ERR_NOTREGISTERED       std::cout << " You have not registered" << std::endl;
# define   ERR_PASSWDMISMATCH  std::cout << " Password incorrect" << std::endl;
# define   ERR_YOUREBANNEDCREEP std::cout << " You are banned from this server" << std::endl;
# define   ERR_INVITEONLYCHAN(a) std::cout << a << " :Cannot join channel (+i)" << std::endl;
# define   ERR_CHANNELISFULL(a) std::cout << a << " :Cannot join channel (+l)" << std::endl;
# define   ERR_BANNEDFROMCHAN(a)   std::cout << a << "  :Cannot join channel (+b)" << std::endl;
# define   ERR_NOPRIVILEGES         std::cout << " :Permission Denied- You're not an IRC operator" << std::endl;
# define   ERR_CANTKILLSERVER    std::cout << " You cant kill a server!" << std::endl;
# define   ERR_ERRONEUSNICKNAME(a)  std::cout << a << " :Erroneus nickname" << std::endl;
