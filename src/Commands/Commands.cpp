/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:39:35 by zrabhi            #+#    #+#             */
/*   Updated: 2023/03/01 19:52:08 by zrabhi           ###   ########.fr       */
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
}

Commands::~Commands()
{
}

std::vector<std::string> Commands::splite(std::string &parametrs, std::string delemiter)
{
    std::vector<std::string> vals;
    size_t position;
	while ((position = parametrs.find(delemiter)) != std::string::npos)
	{
		vals.push_back(parametrs.substr(0, position));
		parametrs.erase(0, position + delemiter.length());
	}
	vals.push_back(parametrs);
	return vals;
}

void    Commands::replyto(std::string _message, int fd)
{
    message = _message;
    send(fd, message.c_str(), message.size(), 0);
} 

void    Commands::makeUpper(std::string &param)
{
    for(std::string::iterator _it = param.begin(); _it != param.end(); _it++ )
    {
        *_it = toupper(*_it);    
    }  
}

void    Commands::commandsErrors(std::string cmd, int fd, size_t index)
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

void    Commands::authentification(std::string &string, std::map<int, Client> &_clients, int fd)
{
    std::vector<std::string> tmp = splite(string, " ");
    makeUpper(tmp[0]);
    tmp[0] = tmp[0].substr(0, tmp[0].find("\n"));
    size_t i = 0;
    BMemFun _commands[] = {&Commands::NICK, &Commands::PASS, &Commands::USER};
    for(i = 0;  i < 3 && tmp[0].compare(authCommands[i]); i++)
    {    
    }
    if (tmp.size() == 1)
    {   
        commandsErrors(tmp[0], fd, i);
        return;
    }
    std::map<int, Client>::iterator _it = _clients.find(fd); 
    _users = _clients;
    tmp[1] = tmp[1].substr(0, tmp[1].find("\n"));
    switch(i)
    {
        case 0:                                                
            if (!validateNick(tmp[1], _clients,  fd))
                {
                    replyto(ERR_NICKNAMEINUSE(tmp[1]), fd);
                    return ;
                }
            (this->*_commands[i])(tmp, _it);
            break ;
        case 1:
            (this->*_commands[i])(tmp, _it);
            break ;
        case 2:
            (this->*_commands[i])(tmp, _it);
            break ;
        default :
            replyto(ERR_UNKNOWNCOMMAND(tmp[0]), _it->first);
    }
    if (_it->second.getPassWord() != "" && _it->second.getNickName() != "" \
            && _it->second.getUserName() != "" &&  _it->second.getStatus() == GUEST)
    {
        _it->second.setStatus(CLIENT);
        Welcome(_it);
    }   
    
}

void    Commands::Welcome(std::map<int ,Client>::iterator _it)
{
    NEW_CLIENT(_it->first, _it->second.getHostName(), _it->second.getPort());
    message = "┬ ┬┌─┐┬  ┌─┐┌─┐┌┬┐┌─┐  ┌┬┐┌─┐  ┬┬─┐┌─┐  ┌─┐┌─┐┬─┐┬  ┬┌─┐┬─┐\n│││├┤ │  │  │ ││││├┤    │ │ │  │├┬┘│    └─┐├┤ ├┬┘└┐┌┘├┤ ├┬┘\n└┴┘└─┘┴─┘└─┘└─┘┴ ┴└─┘   ┴ └─┘  ┴┴└─└─┘  └─┘└─┘┴└─ └┘ └─┘┴└─\n"   ;
    replyto(message, _it->first);
}

bool    Commands::validateNick(std::string nickName, std::map<int ,Client> _user, int fd)
{
    for(std::map<int ,Client>::iterator _it = _user.begin(); _it != _user.end(); _it++)
    {
        if (_it->second.getNickName() != "" && \
            _it->second.getNickName() == nickName && _it->first != fd)
            return (false);   
    }
    return (true);
}

bool    Commands::NICK(std::vector<std::string> params, std::map<int , Client>::iterator &_client)
{
    if (!isalpha(params[1][0]) || params[1].size() > 9)
        return (replyto(ERR_ERRONEUSNICKNAME(params[1]), _client->first), false);
    if (_client->second.getNickName() != "" )
        KNOWNNOWAS(_client->second.getNickName(), params[1]);
    _client->second.setNickName(params[1]);
    replyto(NICKNAMEMESG(params[1]), _client->first);
    return (true);
}

bool  Commands::checkParams(std::string params)
{
   return (params[0] ==':' && isalpha(params[1]) ? true : false);
}

bool     Commands::validateUserName(std::string userName, std::map<int ,Client> _user, int fd)
{
    for(std::map<int ,Client>::iterator _it = _user.begin(); _it != _user.end(); _it++)
    {
        if (_it->second.getUserName() != "" && \
                _it->second.getUserName() == userName && _it->first != fd)
            return (false);   
    }
    return (true);
}

void    Commands::appendToParams(std::vector<std::string> params, std::string &tmp, size_t index)
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
    return (_c == '-' || _c == '[' || _c == ']' || _c == '\/' \
            || _c == '`\'' || _c == '^'  || _c == '{' || _c == '}');
}

bool   Commands::validateParam(std::string param)
{
    std::string::iterator _it = param.begin() + 1;
    std::string::iterator _it_end = param.end(); 
    if (!isalpha(*(param.begin())) || !isSpecial(*(param.begin())))
        return (false);   
    for (; _it != _it_end; _it++)
    {
        if (!iswalpha(*_it) || !isSpecial(*_it) ||  !isalnum(*_it))
            return false;
    }
    return (true);
}

bool    Commands::USER( std::vector<std::string> params, std::map<int , Client>::iterator &_client)
{
    if (params.size() < 5)
        return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first) \
                ,replyto(REPLYUSER(params[0]), _client->first), false);
    else if (!validateUserName(params[1], _users, _client->first))
            return (replyto(ERR_ALREADYUSED, _client->first), false);
    else 
    { 
        std::string tmp;
        if (params.size() == 5)
            params[4] = params[4].substr(0, params[4].find("\n"));
        if (params[4] == "")
            return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first) \
                ,replyto(REPLYUSER(params[0]), _client->first), false);
        appendToParams(params, tmp, 4);
        _client->second.setUserName(params[1]);
        replyto(NEWUSERNAME(params[1]), _client->first);
        _client->second.setRealName(tmp);
        replyto(NEWREALNAME(tmp), _client->first);
    }
    return (true); 
}

bool    Commands::PASS(std::vector<std::string> params, std::map<int , Client>::iterator &_client)
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