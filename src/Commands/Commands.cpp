/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:39:35 by zrabhi            #+#    #+#             */
/*   Updated: 2023/03/03 05:28:00 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "../header.hpp"
# include <ctype.h>  

Commands::Commands()
{
    authCommands.push_back("NICK");
    authCommands.push_back("PASS");
    authCommands.push_back("USER");
    authCommands.push_back("PRIVMSG");
}

Commands::~Commands()
{
}

Vector Commands::splite(String &parametrs, String delemiter)
{
    Vector vals;
    size_t position;
	while ((position = parametrs.find(delemiter)) != String::npos)
	{
		vals.push_back(parametrs.substr(0, position));
		parametrs.erase(0, position + delemiter.length());
	}
	vals.push_back(parametrs);
	return vals;
}

void    Commands::replyto(String _message, int fd)
{
    message = _message;
    send(fd, message.c_str(), message.size(), 0);
} 

void    Commands::makeUpper(String &param)
{
    for(String::iterator _it = param.begin(); _it != param.end(); _it++ )
    {
        *_it = toupper(*_it);    
    }  
}

void    Commands::commandsErrors(String cmd, int fd, size_t index)
{
    switch(index)
    {
        case 0:
            replyto(ERR_NONICKNAMEGIVEN, fd); 
            return;
        case 1:
            replyto(ERR_NEEDMOREPARAMS(cmd), fd);
            replyto(REPLYPASS(cmd), fd);
            return;
        case 2:
            replyto(ERR_NEEDMOREPARAMS(cmd), fd);
            return;
     default:
            replyto(ERR_UNKNOWNCOMMAND(cmd), fd);
    }
}


bool    Commands::authCommandCheck(Vector params, size_t index, Iterator _it, BMemFunGuest _commands[])
{
    switch(index)
    {
        case 0:
             if (!validateNick(params[1], _users,  _it->first))
                {
                    replyto(ERR_NICKNAMEINUSE(params[1]), _it->first);
                    return (false);
                }
            return((this->*_commands[index])(params, _it));
            // return (true);
        case 1:
            return((this->*_commands[index])(params, _it));
            // return (true);
        case 2:
            return((this->*_commands[index])(params, _it));
        //    return (true);
        case 3:
                if (_it->second.getStatus() != GUEST)
                    return((this->*_commands[index])(params, _it));
        default:
            // return (false);
            replyto(ERR_UNKNOWNCOMMAND(params[0]), _it->first);
            return (false);
    }
    return (true);
}

void    Commands::authentification(String &string, Map &_clients, int fd)
{
    Vector tmp = splite(string, " ");
    makeUpper(tmp[0]);
    tmp[0] = tmp[0].substr(0, tmp[0].find("\n"));
    size_t i = 0;
    BMemFunGuest _commands[] = {&Commands::NICK, &Commands::PASS, &Commands::USER, &Commands::PRIVMSG};
    // BMemFunClient  _clientCommands[] = {&Commands::PRIVMSG};
    for(i = 0;  i < 4 && tmp[0].compare(authCommands[i]); i++)
    {    
    }
    if (tmp.size() == 1)
    {   
        commandsErrors(tmp[0], fd, i);
        return;
    }
    Iterator _it = _clients.find(fd); 
    _users = _clients;
    tmp[1] = tmp[1].substr(0, tmp[1].find("\n"));
    authCommandCheck(tmp, i,_it, _commands);
    if (_it->second.getPassWord() != "" && _it->second.getNickName() != "" \
            && _it->second.getUserName() != "" &&  _it->second.getStatus() == GUEST)
    {
        _it->second.setStatus(CLIENT);
        NEW_CLIENT(_it->first, _it->second.getHostName(), _it->second.getPort());
        // Welcome(_it);
    }
}

void    Commands::Welcome(Iterator _it)
{
    message = "┬ ┬┌─┐┬  ┌─┐┌─┐┌┬┐┌─┐  ┌┬┐┌─┐  ┬┬─┐┌─┐  ┌─┐┌─┐┬─┐┬  ┬┌─┐┬─┐\n│││├┤ │  │  │ ││││├┤    │ │ │  │├┬┘│    └─┐├┤ ├┬┘└┐┌┘├┤ ├┬┘\n└┴┘└─┘┴─┘└─┘└─┘┴ ┴└─┘   ┴ └─┘  ┴┴└─└─┘  └─┘└─┘┴└─ └┘ └─┘┴└─\n"   ;
    replyto(message, _it->first);
}

void      Commands::AuthCommands(int fd)
{
    message = "\033[1m\033[37mYou are now connected to the server as `Guest`\nIf you want to be an irc 'CLIENT' you have to register\n";
    message += "Available commands for resgistration: \n          \033[1m\033[33mNICK: <nickname>\n          USER: username> <unused> <unused> <realname>\n          PASS: <password>\n\033[0m";
    replyto(message, fd);
}

// void    Commands::AvailableCommands(Iterator _it)
// {
//     message = "NICK\nUSER\nPASS"
// }

bool    Commands::validateNick(String nickName, Map _user, int fd)
{
    for(Iterator _it = _user.begin(); _it != _user.end(); _it++)
    {
        if (_it->second.getNickName() != "" && \
            _it->second.getNickName() == nickName && _it->first != fd)
            return (false);   
    }
    return (true);
}


bool  Commands::checkParams(String params)
{
   return (params[0] ==':' && isalpha(params[1]) ? true : false);
}

bool     Commands::validateUserName(String userName, Map _user, int fd)
{
    for(Iterator _it = _user.begin(); _it != _user.end(); _it++)
    {
        if (_it->second.getUserName() != "" && \
                _it->second.getUserName() == userName && _it->first != fd)
            return (false);   
    }
    return (true);
}

void    Commands::appendToParams(Vector params, String &tmp, size_t index)
{
    size_t position;
    if (params[index][0] != ':')
    {
        tmp = params[index];
        return;
    }
    tmp = params[index].substr(1, params[index].size());
    for (size_t i = ++index; i < params.size(); i++)
    {
        tmp += " ";
        if ((position = params[i].find("\n")))
            params[i] = params[i].substr(0, position);
        tmp += params[i];
    }
}


bool    Commands::isSpecial(char _c)
{
    return (_c == '-' || _c == '[' || _c == ']' || _c == '\\' \
            || _c == '`' || _c == '^'  || _c == '{' || _c == '}');
}

bool Commands::isAlphaOrSpecial(char _c)
{
    if (iswalpha(_c) || isSpecial(_c))
        return (true);
    return (false); 
}

bool   Commands::validateParam(String param, bool priv)
{
    String::iterator _it = param.begin() + 1;
    size_t checker(1);
    String::iterator _it_end = param.end(); 
    if (priv)
    {
        if (!isAlphaOrSpecial(*(param.begin())))
            return (false);   
    }
    for (; _it != _it_end && (iswalpha(*_it)  || isSpecial(*_it)  || isalnum(*_it)); _it++ )
        checker++;
    if (checker != param.size())
        return (false);
    return (true);
}

bool  Commands::NICK(Vector params, Iterator &_client)
{
    if (!validateParam(params[1], true) || params[1].size() > 9)
        return (replyto(ERR_ERRONEUSNICKNAME(params[1]), _client->first), false);
    if (_client->second.getNickName() != "" )
        KNOWNNOWAS(_client->second.getNickName(), params[1]);
    _client->second.setNickName(params[1]);
    replyto(NICKNAMEMESG(params[1]), _client->first);
    return (true);
}

bool Commands::isNonWhite(char _c, bool priv)
{
    if (priv)
        if (_c == 0x20)
            return (true); 
    return (_c == 0x0 || _c == 0xd || _c == 0xa);
}

bool Commands::validateUser(String param, bool priv)
{
    String::iterator _it = param.begin();
    String::iterator _it_end = param.end(); 
    for (; _it != _it_end ; _it++ )
    {
        if (isNonWhite(*_it, priv))
            return (false);
    }
    return (true);
}

bool    Commands::USER(Vector params, Iterator &_client)
{
    if (params.size() < 5)
        return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first) \
                ,replyto(REPLYUSER(params[0]), _client->first), false);
    else if (!validateUserName(params[1], _users, _client->first))
            return (replyto(ERR_ALREADYUSED, _client->first), false);
    else if (!validateUser(params[1], true))
            return (replyto(ERR_ERRONEUSNICKNAME(params[1]), _client->first), false);
    else 
    { 
        String tmp;
        params[params.size() - 1] = params[params.size() -1].\
        substr(0, params[params.size() -1].find("\n"));
        if (params[4] == "")
            return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first) \
                ,replyto(REPLYUSER(params[0]), _client->first), false);
        appendToParams(params, tmp, 4);
        if (!validateUser(tmp, false))
            return (replyto(ERR_ERRONEUSNICKNAME(tmp), _client->first), false);
        _client->second.setUserName(params[1]);
        replyto(NEWUSERNAME(params[1]), _client->first);
        _client->second.setRealName(tmp);
        replyto(NEWREALNAME(tmp), _client->first);
    }
    return (true); 
}

bool    Commands::PASS(Vector params, Iterator &_client)
{
    if (_client->second.getAuth() == REGISTERD)
    {
        replyto(ERR_ALREADYREGISTRED, _client->first);
        return(false);
    }
    if (params[1] != _client->second.getServerPass())
    {
        replyto(ERR_PASSWDMISMATCH, _client->first);
        return(false);
    }
    _client->second.setPassWord(params[1]);
    _client->second.setAuth(REGISTERD);
    return (true);
}

Iterator    Commands::FindUser(String nickName, int fd)
{
    for(Iterator _it = _users.begin(); _it != _users.end(); _it++)
    {
        if (_it->second.getNickName() == nickName && _it->first != fd)
            return (_it);   
    }
    return (_users.end());
}

bool    Commands::PRIVMSG(Vector params,  Iterator &_client)
{
    if (params.size() < 3)
         return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first),false);
    Iterator   reciever = FindUser(params[1], _client->first);
    if (reciever == _users.end())
           return (replyto(ERR_NOSUCHNICK, _client->first),false);

    else
        {
            String tmp;
            params[params.size() - 1] = params[params.size() -1].\
            substr(0, params[params.size() -1].find("\n"));
            // if (params[2] == "")
            //     return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first), false);
            appendToParams(params, tmp, 2);
            tmp += "\n";
            replyto(tmp, reciever->first);
            std::cout << "Message is sent !" << std::endl;
        }
    return (true);
}

