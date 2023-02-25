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

/*
    COLORS
*/

# define RESET       "\033[0m"
# define RED         "\033[30m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m" 
# define MAGENTA     "\033[35m"      
# define CYAN        "\033[36m"      
# define WHITE       "\033[37m"     
# define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
# define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
# define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
# define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
# define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
# define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
# define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
# define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


# define   ARGS_ERR "Usage: ./ircserv <port> <password>\nport: A number between 1025 and 65536\npassword: a sequence of characeters"
# define   INVALID_ARGS() std::cerr << ARGS_ERR << std::endl
# define   ERR_NONICKNAMEGIVEN  std::cout << BOLDYELLOW <<"Error(431): No nickname given." << RESET << std::endl;
# define   ERR_UNKNOWNCOMMAND(a)  std::cout << "Error(421): "  << a << " Unknown command."  << std::endl;
# define   ERR_NEEDMOREPARAMS(a) std::cout << BOLDYELLOW <<"Error(461): " +  a + " Not enough parameters." << RESET << std::endl;
# define   ERR_NICKNAMEINUSE(a) std::cout << a << " :Nickname is already in use" << std::endl;
# define   ERR_USERNOTINCHANNEL(a, b) std::cout << a << " :They aren't on that channel" << b << std::endl;
# define   ERR_NOTONCHANNEL(a) std::cout << a << " :You're not on that channel" << std::endl;
# define   ERR_USERONCHANNEL(a, b) std::cout << a << " " << b << " :is already on channel" << std::endl;
# define   ERR_SUMMONDISABLED(a)  std::cout << a << " has been disabled" << std::endl;
# define   ERR_NOTREGISTERED   std::cout << " You have not registered" << std::endl;
# define   ERR_PASSWDMISMATCH  std::cout << " Password incorrect" << std::endl;
# define   ERR_YOUREBANNEDCREEP std::cout << " You are banned from this server" << std::endl;
# define   ERR_INVITEONLYCHAN(a) std::cout << a << " :Cannot join channel (+i)" << std::endl;
# define   ERR_CHANNELISFULL(a) std::cout << a << " :Cannot join channel (+l)" << std::endl;
# define   ERR_BANNEDFROMCHAN(a) std::cout << a << "  :Cannot join channel (+b)" << std::endl;
# define   ERR_NOPRIVILEGES  std::cout << " :Permission Denied- You're not an IRC operator" << std::endl;
# define   ERR_CANTKILLSERVER std::cout << " You cant kill a server!" << std::endl;
# define   ERR_ERRONEUSNICKNAME(a)  std::cout << "Error(432): " + a << " Erroneus nickname." << std::endl;

/*
    SERVER REPLY
*/

#if a 
    {
        # define REPLY_PASS(a) std:: cout << BOLDGREEN << "Reply(650) : PASS <password>" 
    }
// #else
// {
//     std::cout << "else\n";
// }
#endif

# define REPLY_PASS(a) std:: cout << BOLDGREEN << "Reply(650) : PASS <password>" << RESET << std::endl; 
# define KNOWNAS(a)  std::cout << BOLDCYAN  << "You are known as " + a << RESET << std::endl;