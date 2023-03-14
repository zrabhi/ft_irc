/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:39:35 by zrabhi            #+#    #+#             */
/*   Updated: 2023/03/14 14:17:57 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Commands.hpp"
# include "../header.hpp"
# include <ctype.h>
# include <sstream>

Commands::BMemFunGuest _commands[] = {&Commands::NICK, &Commands::PASS,
                                &Commands::USER, &Commands::PRIVMSG,
                                &Commands::JOIN, &Commands::NOTICE,
                                &Commands::PART,&Commands::KICK,
                                &Commands::TOPIC, &Commands::BOT};
Commands::Commands()
{
    authCommands.push_back("NICK");
    authCommands.push_back("PASS");
    authCommands.push_back("USER");
    authCommands.push_back("PRIVMSG");
    authCommands.push_back("JOIN");
    authCommands.push_back("NOTICE");
    authCommands.push_back("PART");
    authCommands.push_back("KICK");
    authCommands.push_back("TOPIC");
    authCommands.push_back("BOT");
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
    std::string tmp;
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
    if (index > 2 && index < 9 &&  _it->second.getStatus() != CLIENT )
         return (replyto(ERR_NOTREGISTERED, _it->first), false);
    switch (index)
    {
        case 0:
            replyto(ERR_NONICKNAMEGIVEN, _it->first); 
        case 1:
            return (replyto(ERR_NEEDMOREPARAMS(cmd), _it->first), false);
        case 2:
            return (replyto(ERR_NEEDMOREPARAMS(cmd), _it->first), false);
        case 3:
            return (replyto(ERR_NORECIPIENT(cmd), _it->first), false);
        case 4:
            return (replyto(ERR_NEEDMOREPARAMS(cmd), _it->first), false);
        case 5:
            return (false);
        case 6 :
            return (replyto(ERR_NEEDMOREPARAMS(cmd), _it->first), false);
        case 7:
            return (replyto(ERR_NEEDMOREPARAMS(cmd), _it->first), false);
        case 8:
            return (replyto(ERR_NEEDMOREPARAMS(cmd), _it->first), false); 
        case 9:
            return (false);
     default:
            return (replyto(ERR_UNKNOWNCOMMAND(cmd), _it->first), false);
    }
    return (false);
}

bool    Commands::authCommandCheck(Vector params, size_t index, Iterator _it, BMemFunGuest _commands[])
{
    if (index > 2 && index < 9 && _it->second.getStatus() != CLIENT)
        return (replyto(ERR_NOTREGISTERED, _it->first), false);
    switch (index)
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
            return((this->*_commands[index])(params, _it));
        case 4:
            return((this->*_commands[index])(params, _it));
        case 5:
            return((this->*_commands[index])(params, _it));
        case 6:
            return((this->*_commands[index])(params, _it));
        case 7:
            return((this->*_commands[index])(params, _it));
        case 8:
            return((this->*_commands[index])(params, _it));
        case 9:
            return((this->*_commands[index])(params, _it));
        default:
            return(replyto(ERR_UNKNOWNCOMMAND(params[0]), _it->first), false);
    }
    return (true);
}

String Commands::currentTime()
{
   time_t now(time(0));
   String value;
   char* dt(ctime(&now));
   
   value = dt;
   return (value.substr(0, value.find("\n")));
}

void    Commands::countUsers(int &numbers)
{
    Iterator _it = _users.begin();
    for(;_it != _users.end();_it++)
        numbers++;
}

void    Commands::Welcome(String nickName, String userName, String hostName, int reciever)
{
    int number;

    number = 0;
    countUsers(number);
    replyto(RPL_WELCOME(nickName, userName, hostName), reciever);
    replyto(RPL_YOURHOST(nickName), reciever);
    replyto(RPL_CREATED(nickName, currentTime()), reciever);
    replyto(RPL_MYINFO(nickName), reciever);
    replyto(RPL_LUSERCLIENT(nickName, String(std::to_string(number))), reciever);
    replyto(RPL_INFO1(nickName),  reciever);
    replyto(RPL_INFO2(nickName),  reciever);
    replyto(RPL_INFO3(nickName),  reciever);
    replyto(RPL_INFO(nickName),   reciever);
    replyto(RPL_BOT(nickName),    reciever);
    replyto(RPL_LAST(nickName),   reciever);
}

void    Commands::WelcomeGuest(int reciever)
{
    replyto(NOTICE1, reciever);
	replyto(NOTICE2, reciever);
	replyto(NOTICEGUEST, reciever);
	replyto(AV_COMMANDS, reciever);
}

void    Commands::setPrivelege(Iterator &_it)
{
   
    if (_it->second.getPassWord() != "" && _it->second.getNickName() != "" \
                && _it->second.getUserName() != "" &&  _it->second.getStatus() == GUEST)
    {
       _it->second.setStatus(CLIENT);
       Welcome(_it->second.getNickName(), _it->second.getUserName(),_it->second.getHostName(),_it->first);
       NEW_CLIENT(_it->second.getNickName(), _it->second.getHostName(), _it->second.getPort());
    }
}

bool    Commands::ignoredCommands(String cmd)
{
    if (!cmd.compare("QUIT") || !cmd.compare("AWAY") || !cmd.compare("PING") \
            || !cmd.compare("MODE") || !cmd.compare("WHO") || !cmd.compare("ISON") \
                || !cmd.compare("PONG"))
        return (false);
    return (true);
}

void    Commands::authentification(String &string, Map &_clients, int fd)
{
    _users = _clients;
    Iterator _it = _clients.find(fd); 
    size_t i = 0;
    
    Vector tmp = splite(string, " ");
    if (tmp.size() == 0 || !ignoredCommands(tmp[0]))
        return ;
    makeUpper(tmp[0]);
    for (i = 0;  i < 10 && tmp[0].compare(authCommands[i]); i++);
    if (tmp.at(0) != "BOT" && (tmp.size() == 1 || tmp[1] == ":"))
    {   
        commandsErrors(tmp[0], _it, i);
        return;
    }
    if (!authCommandCheck(tmp, i,_it, _commands))
        return ;
    setPrivelege(_it);
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
        tmp += params[index];
        return;
    }
    // if (params[index].size() > 2 && params[index][0] == ':' &&  params[index][1] == ':' )
    //     return ;
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

bool Commands::FindUsersInChannel(String channelName,Vector_map &Users, int fd)
{
    (void)fd;
    ChannelMap::iterator _it =  _channels.find(channelName);
    
    if (_it == _channels.end())
        return (false);
    return (Users.insert(std::make_pair(channelName, _it->second.getUsers())), true);
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

bool  Commands::checkUsers(Vector param, Vector_it &parameters, Vector_map &Users, size_t index, int fd)
{
    Iterator  value; 
    Vector_it channelUsers; 
    Vector    splited;

    splited = splite(param[index], ",");
    for (Vector::iterator _it = splited.begin(); _it != splited.end(); _it++)
    { 
        if (isHash((*_it)[0]))
        {
            if (!FindUsersInChannel(*_it, Users, fd))
                return (false);
            continue;
        }
        value = FindUser(*_it, fd);
        if (value == _users.end())
            return (false);
        parameters.push_back(value);
    }
    return (true);
}


bool Commands::validateChannel(String channelName)
{
    ChannelMap::iterator _it = _channels.begin();
    
    for (;_it != _channels.end(); _it++)
    {
        if (channelName == _it->first)
            return (true);
    }    
    return (false);

}