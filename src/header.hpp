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
};

# define RESET       "\033[0m"
# define RED         "\033[30m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m" 
# define MAGENTA     "\033[35m"      
# define CYAN        "\033[36m"      
# define WHITE       "\033[37m"     

# define BOLDBLACK   "\033[1m\033[30m"    
# define BOLDRED     "\033[1m\033[31m"     
# define BOLDGREEN   "\033[1m\033[32m"    
# define BOLDYELLOW  "\033[1m\033[33m"    
# define BOLDBLUE    "\033[1m\033[34m"    
# define BOLDMAGENTA "\033[1m\033[35m"    
# define BOLDCYAN    "\033[1m\033[36m"    
# define BOLDWHITE   "\033[1m\033[37m"    


# define   ARGS_ERR                         "Usage: ./ircserv <port> <password>\nport: A number between 1025 and 65536\npassword: a sequence of characeters"
# define   INVALID_ARGS                      std::cerr << ARGS_ERR << std::endl

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
# define   CLOSINGLINK(a)                    "ERROR :Closing Link: localhost (Quit: " + a +")\r\n"


# define  NEW_CLIENT(a, b, c)  std::cout << "New client <" << a << "> added from " << b << ":" << c << std::endl;
# define  REPLYUSER(a)   BOLDGREEN + a + " <username> <unused> <unused> :<realname> " + RESET + "\n"


# define  NOTICE1                ":localhost NOTICE AUTH :*** Looking up for your hostname...\r\n"
# define  NOTICE2                ":localhost NOTICE AUTH :*** Found your hostname\r\n"  
# define  RPL_LUSERCLIENT(a)    ":localhost 251 :There are " + a[0] + " users and 1 server"
# define  RPL_WELCOME(a,b,c)    ":localhost 001 " + a +  " :Welcome to the Internet Relay Network " + a + "!"+ b +"@" + c + "\r\n"
# define  RPL_YOURHOST(a)       ":localhost 002 " + a +  " :Your host is ft_irc_server, running version 1.1.2\r\n"
# define  RPL_CREATED(a, b)     ":localhost 003 " + a +  " :This server was created " + b + "\r\n"  
# define  RPL_MYINFO(a)         ":localhost 004 " + a +  " :localhost 1.0 - -\r\n"    
# define  RPL_INFO(a)           ":localhost 372 " + a +  " :Please enjoy your stay!\r\n"
# define  RPL_INFO1(a)          ":localhost 372 " + a +  " :         ┬ ┬┌─┐┬  ┌─┐┌─┐┌┬┐┌─┐  ┌┬┐┌─┐  ┬┬─┐┌─┐  ┌─┐┌─┐┬─┐┬  ┬┌─┐┬─┐\r\n"
# define  RPL_INFO2(a)          ":localhost 372 " + a +  " :         │││├┤ │  │  │ ││││├┤    │ │ │  │├┬┘│    └─┐├┤ ├┬┘└┐┌┘├┤ ├┬┘\r\n"
# define  RPL_INFO3(a)          ":localhost 372 " + a +  " :         └┴┘└─┘┴─┘└─┘└─┘┴ ┴└─┘   ┴ └─┘  ┴┴└─└─┘  └─┘└─┘┴└─ └┘ └─┘┴└─\r\n"
# define  RPL_INFO4(a)           ":localhost 372 " + a + " : "
# define  RPL_LAST(a)            ":localhost 376 " + a +  " :Made by ooumlil && zrabhi\r\n"

# define ERR_BOT                ":461 ERR_NEEDMOREPARAMS :Use BOT help for more informations\r\n"
