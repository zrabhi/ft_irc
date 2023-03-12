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
# include "Commands/Commands.hpp"




enum T_flag
{   
    NOT_REGISTERED = 0,
    REGISTERD = 1,
    GUEST,
    CLIENT,
    O,
    o,
};

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


# define   ARGS_ERR                         "Usage: ./ircserv <port> <password>\nport: A number between 1025 and 65536\npassword: a sequence of characeters"
# define   INVALID_ARGS()                   std::cerr << ARGS_ERR << std::endl
# define   ERR_USERNOTINCHANNEL(a, b)       std::cout << a << " :They aren't on that channel" << b << std::endl;
# define   ERR_USERONCHANNEL(a, b)          std::cout << a << " " << b << " :is already on channel" << std::endl;
# define   ERR_SUMMONDISABLED(a)            std::cout << a << " has been disabled" << std::endl;
# define   ERR_YOUREBANNEDCREEP             std::cout << " You are banned from this server" << std::endl;
# define   ERR_INVITEONLYCHAN(a)            std::cout << a << " :Cannot join channel (+i)" << std::endl;
# define   ERR_CHANNELISFULL(a)             std::cout << a << " :Cannot join channel (+l)" << std::endl;
# define   ERR_BANNEDFROMCHAN(a)            std::cout << a << "  :Cannot join channel (+b)" << std::endl;
# define   ERR_NOPRIVILEGES                 std::cout << " :Permission Denied- You're not an IRC operator" << std::endl;
# define   ERR_CANTKILLSERVER               std::cout << " You cant kill a server!" << std::endl;

# define   ERR_ALREADYREGISTRED             "451 ERR_NOTREGISTERED :You have not registered\r\n" 
# define   ERR_NEEDMOREPARAMS(a)            "461 ERR_NEEDMOREPARAMS <" + a +">:Not enough parameters\r\n"
# define   ERR_NORECIPIENT(a)               "411 ERR_NORECIPIENT :No recipient given("+ a+ ")\r\n"
# define   ERR_PASSWDMISMATCH               "464 ERR_PASSWDMISMATCH:Password incorrect\r\n"
# define   ERR_NONICKNAMEGIVEN              "431 ERR_NONICKNAMEGIVEN :No nickname given\r\n" 
# define   ERR_ERRONEUSNICKNAME(a)          "432 ERR_ERRONEUSNICKNAME <"+a+"> :Erroneus nickname\r\n"
# define   ERR_NICKNAMEINUSE(a)             "433 ERR_NICKNAMEINUSE <"+a+"> :Nickname is already in use\r\n"
# define   ERR_NOSUCHNICK(a)                "401 ERR_NOSUCHNICK<" + a +"> :No such nick/channel\r\n"
# define   ERR_UNKNOWNCOMMAND(a)            "421 ERR_UNKNOWNCOMMAND <" + a +"> :Unknown command\r\n"
# define   ERR_BADCHANNELKEY(a)             "475 ERR_BADCHANNELKEY <" + a + "> :Cannot join channel (+k)\r\n"
# define   ERR_NOSUCHCHANNEL(a)             "403 ERR_NOSUCHCHANNEL <" + a + "> :No such channel\r\n"
# define   ERR_TOOMANYCHANNELS(a)           "405 ERR_TOOMANYCHANNELS <" + a +  "> :You have joined too many channels\r\n"
# define   ERR_NOTONCHANNEL(a)              "442 ERR_NOTONCHANNEL " + a + " :You're not on that channel\r\n"
# define   REPLY_PART(a,c, d)               ":" + a + "!" + c + "@localhost PART " + d + " "
# define   REPLY_KICK(a,b,c)                ":" + a + " KICK " + b + " " + c + " "
# define   ERR_NOTREGISTERED                "451 ERR_NOTREGISTERED:You have not registered\r\n"
# define   LISTUSERS(a,b)                   ":localhost 353 " + a + " = "  + b + " "
# define   ENDLIST(a,b)                     ":localhost 366 " + a + " " + b + " :End of /NAMES list.\r\n"
# define   ERR_NOTEXTTOSEND                 "412 ERR_NOTEXTTOSEND:No text to send\r\n"
# define   NOTICE_MSG(a, b, c)              ":" + a + " NOTICE " + b + " :" + c + "\r\n" 
# define   ERR_CHANOPRIVSNEEDED(a)          "482 ERR_CHANOPRIVSNEEDED <" + a + ">:You're not channel operator\r\n"
# define   RPL_NOTOPIC(a)                   "331 RPL_NOTOPIC " + a + " :No topic is set\r\n"
# define   RPL_TOPIC(a,c,b)                 ":" + a + "!" + c + "@localhost TOPIC " + b + " :"
# define   REPLY_PIVMSG(a, b, c, d)         ":" + a + "!" + b + "@localhost PRIVMSG " + c +  " :" + d + "\r\n" 
# define   RFEPLY_CHANNEL(a, c, b)          ":" + a + "!" + c + "@localhost JOIN " + b + "\r\n"



# define  NICKNAMEMESG(a)  "\033[1m\033[33myou are known as " +  a  +  RESET + "\n"
# define  KNOWNNOWAS(a, b) std::cout << "\033[1m\033[32m" + a + " is now known as " + b + RESET << std::endl;
# define  NEW_CLIENT(a, b, c)   std::cout << "New client #" << a << " added from " << b << ":" << c << std::endl;
# define  REPLYPASS(a)   "\033[1m\033[32mReply(650) : PASS <password>\n\033[0m"
# define  REPLYUSER(a)   BOLDGREEN + a + " <username> <unused> <unused> :<realname> " + RESET + "\n"
# define  KNOWNAS(a)  std::cout << BOLDCYAN  << "You are known as " + a << RESET << std::endl;
# define  REPLYACCESS std::cout <<  BOLDGREEN << "Reply(650) : You dont have privilege " << RESET << std::endl; 
# define  ERR_ALREADYUSED  "\033[1m\033[33m:Username is already in use \033[0m\n" 
# define  NEWUSERNAME(a)  BOLDYELLOW + a + " is your username" + RESET + "\n"
# define  NEWREALNAME(a)  BOLDYELLOW + a + " is your realname" + RESET + "\n"

# define  REPLYPRIVMSG       "\033[1m\033[33m<receiver> <text to be sent>\n\033[1m"
# define  RPL_YOURHOST       "002 RPL_YOURHOST Your host is ft_irc_server, running version 1.1.2\r\n"
# define  RPL_CREATED(a)     "003 RPL_CREATED This server was created " + a + "\r\n"  
# define  RPL_WELCOME(a,b,c) "001 RPL_WELCOME Welcome to the Internet Relay Network " + a + "!"+ b +"@" + c + "\r\n"
#if a 
    {
        # define REPLY_PASS(a) std:: cout << BOLDGREEN << "Reply(650) : PASS <password>" 
    }
// #else
// {
//     std::cout << "else\n";
// }
#endif