/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:28:24 by zrabhi            #+#    #+#             */
/*   Updated: 2023/03/03 04:50:40 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <vector>
# include "../client/client.hpp"
# include <map> 

class Commands
{
    public:
                                /*PRIVATE VB*/
        typedef std::map<int , Client>  Map;
        typedef std::string             String;
        typedef std::vector<String>     Vector;
        typedef  Map::iterator          Iterator;
        typedef bool(Commands::*BMemFunGuest) (Vector param, Iterator &_client);
        typedef bool(Commands::*BMemFunClient) (Vector param, Iterator &_client);
    private:
        Map     _users;
        Vector   authCommands;
        String              message;
                                /*PRIVATE FUCNTION */
        void    commandsErrors(String cmd, int fd, size_t index);
       
        Vector splite(String &parametrs, String delemiter);
        void    makeUpper(String &param);
        void    appendToParams(Vector params, String &tmp, size_t index);
        Iterator    FindUser(String nickName, int fd);
        bool    checkParams(String params);
       
        bool    validateParam(String param,bool priv);
        bool    validateNick(String nickName, Map _user, int fd);
        bool    validateUserName(String userName, Map _user, int fd);
        bool    validateUser(String param, bool priv);
        bool    isSpecial(char _c);
        bool    isAlphaOrSpecial(char _c);
        bool    isNonWhite(char _c, bool priv);
        
    public:
        Commands();
        ~Commands();
        void    authentification(String &string, Map &_clients, int fd);
        void    Welcome(Iterator _it);
        void    AvailableCommands(Map _it);
        void    AuthCommands(int fd);
        void    replyto(String message, int fd);
    
        bool    NICK(Vector params,  Iterator &_client);      
        bool    PASS(Vector params,  Iterator &_client);
        bool    USER(Vector params,  Iterator &_client);  
        bool    PRIVMSG(Vector params,  Iterator &_client);
        bool    authCommandCheck(Vector params, size_t index, Iterator _it, BMemFunGuest _commands[]);
};

typedef Commands::Vector    Vector;
typedef Commands::Map       Map;
typedef Commands::String    String;
typedef Commands::Iterator  Iterator;


#endif