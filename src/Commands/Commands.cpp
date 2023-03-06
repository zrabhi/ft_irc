/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:39:35 by zrabhi            #+#    #+#             */
/*   Updated: 2023/03/06 01:56:43 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Commands.hpp"
# include "../header.hpp"
# include <ctype.h>
# include <sstream>
// # include "NICK"
Commands::BMemFunGuest _commands[] = {&Commands::NICK, &Commands::PASS,
                                &Commands::USER, &Commands::PRIVMSG,
                                &Commands::JOIN};
Commands::Commands()
{
    authCommands.push_back("NICK");
    authCommands.push_back("PASS");
    authCommands.push_back("USER");
    authCommands.push_back("PRIVMSG");
    authCommands.push_back("JOIN");
}

Commands::~Commands()
{
}

Vector Commands::splite(String &parametrs,  String delemiter)
{
	Vector splited;
	for (char *token = std::strtok(const_cast<char *>(parametrs.c_str()), delemiter.c_str());\
         token != NULL; token = std::strtok(nullptr, delemiter.c_str()))
		splited.push_back(token);
	return (splited);
}

void    Commands::replyto(String _message, int fd)
{
    message = _message;
    send(fd, message.c_str(), message.size(), 0);
} 

void    Commands::makeUpper(String &param)
{
    String::iterator _it;
    String::iterator _it_end; 

    _it = param.begin();
    _it_end = param.end();
    if (_it == _it_end)
        return ;
    for(; _it != _it_end; _it++)
        *_it = toupper(*_it);    
}

bool    Commands::commandsErrors(String cmd, Iterator _it, size_t index)
{
    switch(index)
    {
        case 0:
            replyto(ERR_NONICKNAMEGIVEN, _it->first); 
        case 1:
            return (replyto(ERR_NEEDMOREPARAMS(cmd), _it->first), false);
        case 2:
            return (replyto(ERR_NEEDMOREPARAMS(cmd), _it->first), false);
        case 3:
            if (_it->second.getStatus() == CLIENT)
                return (replyto(ERR_NORECIPIENT(cmd), _it->first), false);
            return (replyto(ERR_UNKNOWNCOMMAND(cmd), _it->first), false);
        case 4:
            if (_it->second.getStatus() == CLIENT)
                return (replyto(ERR_NEEDMOREPARAMS(cmd), _it->first), false);
            return (replyto(ERR_UNKNOWNCOMMAND(cmd), _it->first), false);
     default:
            return (replyto(ERR_UNKNOWNCOMMAND(cmd), _it->first), false);
    }
    return (false);
}


bool    Commands::authCommandCheck(Vector params, size_t index, Iterator _it, BMemFunGuest _commands[])
{
    switch(index)
    {
        case 0:
             if (!validateNick(params[1], _users,  _it->first))
                    return (replyto(ERR_NICKNAMEINUSE(params[1]), _it->first), false);
            return((this->*_commands[index])(params, _it));
        case 1:
            return((this->*_commands[index])(params, _it));
        case 2:
            return((this->*_commands[index])(params, _it));
        case 3:
            if (_it->second.getStatus() != GUEST)
                return((this->*_commands[index])(params, _it));
        case 4:
            if (_it->second.getStatus() != GUEST)
                return((this->*_commands[index])(params, _it));
        default:
            return(replyto(ERR_UNKNOWNCOMMAND(params[0]), _it->first), false);
    }
    return (true);
}

String Commands::currentTime()
{
   time_t now(time(0));
   char* dt(ctime(&now));
   std::string value(dt);
   
   return (value.substr(0, value.find("\n")));
}

void    Commands::setPrivelege(Iterator &_it)
{
    if (_it->second.getPassWord() != "" && _it->second.getNickName() != "" \
                && _it->second.getUserName() != "" &&  _it->second.getStatus() == GUEST)
    {
       _it->second.setStatus(CLIENT);
       replyto(RPL_YOURHOST, _it->first);
       replyto(RPL_CREATED(currentTime()), _it->first);
       NEW_CLIENT(_it->first, _it->second.getHostName(), _it->second.getPort());
    }
}

void    Commands::authentification(String &string, Map &_clients, int fd)
{
    Vector tmp1 = splite(string, "\r\n");
    for (size_t j = 0; j < tmp1.size(); j++)
    {
        Vector tmp = splite(tmp1[j], " ");
        makeUpper(tmp[0]);
        size_t i = 0;
        for(i = 0;  i < 5 && tmp[0].compare(authCommands[i]); i++);
        if (tmp.size() == 1 || tmp[1] == ":")
        {   
            commandsErrors(tmp[0], _clients.find(fd), i);
            return;
        }
        Iterator _it = _clients.find(fd); 
        _users = _clients;
        if (!authCommandCheck(tmp, i,_it, _commands))
            return ;
        setPrivelege(_it);
    }
}

bool  Commands::validateNick(String nickName, Map _user, int fd)
{
    Iterator _it;
    Iterator _it_end; 
    
    _it = _user.begin();
    _it_end = _user.end();
    for(; _it != _it_end; _it++)
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

bool Commands::validateUserName(String userName, Map _user, int fd)
{
    Iterator _it;
    Iterator _it_end; 
    
    _it = _user.begin();
    _it_end = _user.end();
    for (; _it != _it_end; _it++)
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
    if (params[index].size() > 2 && params[index][0] == ':' &&  params[index][1] == ':' )
        return ;
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
    String::iterator _it;
    String::iterator _it_end; 
    size_t checker;
  
    checker = 1;
    _it = param.begin() + 1;
    _it_end = param.end();
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

bool Commands::isNonWhite(char _c, bool priv)
{
    if (priv)
        if (_c == 0x20)
            return (true); 
    return (_c == 0x0 || _c == 0xd || _c == 0xa);
}

bool Commands::validateUser(String param, bool priv)
{
    String::iterator _it;
    String::iterator _it_end; 
    
    _it = param.begin();
    _it_end = param.end();
    for (; _it != _it_end ; _it++ )
    {
        if (isNonWhite(*_it, priv))
            return (false);
    }
    return (true);
}


bool  Commands::isComma(char _c)
{
    return (_c == ',');
}

bool Commands::isHash(char _c)
{
    return (_c == '#');
}

Iterator Commands::FindUser(String nickName, int fd)
{
    Iterator _it;
    Iterator _it_end; 
    
    _it = _users.begin();
    _it_end = _users.end();
    for (; _it != _it_end; _it++)
    {
        if (_it->second.getNickName() == nickName && _it->first != fd)
            return (_it);
    }
    return (_it_end);
}

bool  Commands::checkUsers(Vector param, Vector_it &parameters, size_t index, int fd)
{
    Iterator  value;
    Vector    splited;

    splited = splite(param[index], ",");
    for (Vector::iterator _it = splited.begin(); _it != splited.end(); _it++)
    {
        value = FindUser(*_it, fd);
        if (value == _users.end())
            return (false);
        parameters.push_back(value);
    }
    return (true);
}


bool  Commands::JOIN(Vector params, Iterator &_client)
{
    if (params.size() - 1 >= 2)
    {
        Vector channelNames = splite(params.at(1), ",");
        // Vector::iterator itNames = channelNames.begin();
        Vector channelKeys = splite(params.at(2), ",");
        // Vector::iterator itKeys = channelKeys.begin();
        // for (; itKeys != params.end(); ++itKeys)
        // to-do: check if channel exists and add it to channel map with password
    }
    else if (params.size() - 1 == 1 && params.at(params.size() - 1) == "")
    {
        replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first);
    }
    else
    {
        // to-do: check if channel exists and add it to channel map without password
    }
    // Channel channel(channelName, "", _client->second);
    return (true);
}
