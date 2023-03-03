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
// #include "Commands/Commands.hpp"
// # include "./server/server.hpp"
enum T_flag
{   
    NOT_REGISTERED = 0,
    REGISTERD = 1,
    GUEST,
    CLIENT,
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
# define   ERR_NICKNAMEINUSE(a)  "\033[1m\033[33m:Nickname is already in use\n\033[0m"
# define   ERR_USERNOTINCHANNEL(a, b) std::cout << a << " :They aren't on that channel" << b << std::endl;
# define   ERR_NOTONCHANNEL(a) std::cout << a << " :You're not on that channel" << std::endl;
# define   ERR_USERONCHANNEL(a, b) std::cout << a << " " << b << " :is already on channel" << std::endl;
# define   ERR_SUMMONDISABLED(a)  std::cout << a << " has been disabled" << std::endl;
# define   ERR_NOTREGISTERED   std::cout << " You have not registered" << std::endl;
# define   ERR_PASSWDMISMATCH   "\033[1m\033[33m:Password incorrect\n\033[0m"
# define   ERR_YOUREBANNEDCREEP std::cout << " You are banned from this server" << std::endl;
# define   ERR_INVITEONLYCHAN(a) std::cout << a << " :Cannot join channel (+i)" << std::endl;
# define   ERR_CHANNELISFULL(a) std::cout << a << " :Cannot join channel (+l)" << std::endl;
# define   ERR_BANNEDFROMCHAN(a) std::cout << a << "  :Cannot join channel (+b)" << std::endl;
# define   ERR_NOPRIVILEGES  std::cout << " :Permission Denied- You're not an IRC operator" << std::endl;
# define   ERR_CANTKILLSERVER std::cout << " You cant kill a server!" << std::endl;
# define   ERR_ERRONEUSNICKNAME(a)  BOLDYELLOW  + a + " :Erroneus nickname." + RESET + "\n"
# define   ERR_ALREADYREGISTRED     "\033[1m\033[33mError(462): You may not reregister\n\033[0m" 
# define   ERR_UNKNOWNCOMMAND(a)  BOLDYELLOW  + a + " Unknown command." + RESET +"\n"
# define   ERR_NONICKNAMEGIVEN  "\033[1m\033[33m:No nickname given.\n\033[0m" 
# define   ERR_NEEDMOREPARAMS(a) "\033[1m\033[33mError(461): " +  a + " Not enough parameters." +RESET +"\n"
# define   ERR_NORECIPIENT     "\033[1m\033[33m:No recipient given n.\n\033[0m"
# define   ERR_NOTEXTTOSEND    "\033[1m\033[33m:No text to send.\n\033[0m"
# define   ERR_NOSUCHNICK      "\033[1m\033[33m:<nickname> :No such nick/channel.\n\033[0m"
/* 
    SERVER REPLY
*/
# define  NICKNAMEMESG(a)  "\033[1m\033[33myou are known as " +  a  +  RESET + "\n"
# define  KNOWNNOWAS(a, b) std::cout << "\033[1m\033[32m" + a + " is now known as " + b + RESET << std::endl;
# define NEW_CLIENT(a, b, c)   std::cout << "New client #" << a << " added from " << b << ":" << c << std::endl;
# define REPLYPASS(a)   "\033[1m\033[32mReply(650) : PASS <password>\n\033[0m"
# define REPLYUSER(a)   BOLDGREEN + a + " <username> <unused> <unused> :<realname> " + RESET + "\n"
# define KNOWNAS(a)  std::cout << BOLDCYAN  << "You are known as " + a << RESET << std::endl;
# define REPLYACCESS std::cout <<  BOLDGREEN << "Reply(650) : You dont have privilege " << RESET << std::endl; 
# define ERR_ALREADYUSED  "\033[1m\033[33m:Username is already in use \033[0m\n" 
# define NEWUSERNAME(a)  BOLDYELLOW + a + " is your username" + RESET + "\n"
# define NEWREALNAME(a)  BOLDYELLOW + a + " is your realname" + RESET + "\n"
# define REPLYPRIVMSG   "\033[1m\033[33m<receiver> <text to be sent>\n\033[1m"
#if a 
    {
        # define REPLY_PASS(a) std:: cout << BOLDGREEN << "Reply(650) : PASS <password>" 
    }
// #else
// {
//     std::cout << "else\n";
// }
#endif