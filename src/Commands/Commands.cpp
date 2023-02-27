/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:39:35 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/27 21:23:15 by zrabhi           ###   ########.fr       */
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

void    Commands::makeUpper(std::string &param)
{
    for(std::string::iterator _it = param.begin(); _it != param.end(); _it++ )
    {
        *_it = toupper(*_it);    
    }  
}

void    Commands::commandsErrors(std::string cmd)
{
    /*
        reminder : to use switch case;
    */
    if (!cmd.compare(0, 4, "NICK"))
    {
        ERR_NONICKNAMEGIVEN;
        return;
    }
    if(!cmd.compare(0, 4, "PASS"))
    {
        ERR_NEEDMOREPARAMS(cmd);
        REPLYPASS(cmd);
        return;
    }
    else if (!cmd.compare(0, 4, "USER"))
    {
        ERR_NEEDMOREPARAMS(cmd);
        return;
    }
    ERR_UNKNOWNCOMMAND(cmd);
}

void    Commands::authentification(std::string &string, std::map<int, Client> &_clients, int fd)
{
    std::vector<std::string> tmp = splite(string, " ");
    makeUpper(tmp[0]);
    if (tmp.size() == 1)
    {   
        commandsErrors(tmp[0].substr(0, tmp[0].find("\n")));
        return;
    }
    size_t i = 0;
    // std::vector<std::string> cmdChecks;
    // authCommands.push_back("NICK");
    // cmdChecks.push_back("PASS");
    // cmdChecks.push_back("USER");
    BMemFun _commands[] = {&Commands::NICK, &Commands::PASS, &Commands::USER};
    for(i = 0;  i < 3 && tmp[0].compare(authCommands[i]); i++)
    {    
    }
    std::map<int, Client>::iterator _it = _clients.find(fd); 
    if (_it->second._auth == REGISTERD && i == 2)
            ERR_ALREADYREGISTRED;    
            //segfault;
    _users = _clients;
    switch(i)
    {
        case 0:                                                
            if (!validateNick(tmp[1].substr(0, tmp[1].find("\n")), _clients,  fd))
                {
                    std::cout << "in condition\n";
                    ERR_NICKNAMEINUSE(tmp[1])
                    return ;
                }
            (this->*_commands[i])(tmp[1].substr(0, tmp[1].find("\n")), _it);
            break ;
        case 1:
            (this->*_commands[i])(tmp[1].substr(0, tmp[1].find("\n")), _it);
            break ;
        case 2:
            (this->*_commands[i])(tmp[1].substr(0, tmp[1].find("\n")), _it);
            break ;
        default :
            ERR_UNKNOWNCOMMAND(tmp[0]);
    }
    if (_it->second.passWord != "" && _it->second._nickname != "" &&  _it->second._status == GUEST)
    {
        _it->second._status = CLIENT;
        Welcome(_it);
    }   
    
}

void    Commands::Welcome(std::map<int ,Client>::iterator _it)
{
    NEW_CLIENT(_it->first, _it->second._hostname, _it->second._port);
    message = "╦ ╦┌─┐┬  ┌─┐┌─┐┌┬┐  ┌┬┐┌─┐  ┬┬─┐┌─┐  ┌─┐┌─┐┬─┐┬  ┬┌─┐┬─┐\n║║║├┤ │  │  │ ││││   │ │ │  │├┬┘│    └─┐├┤ ├┬┘└┐┌┘├┤ ├┬┘\n╚╩╝└─┘┴─┘└─┘└─┘┴ ┴   ┴ └─┘  ┴┴└─└─┘  └─┘└─┘┴└─ └┘ └─┘┴└─\n"   ;
    send(_it->first, message.c_str(), 434, 0);
}

bool    Commands::validateNick(std::string nickName, std::map<int ,Client> _user, int fd)
{
    for(std::map<int ,Client>::iterator _it = _user.begin(); _it != _user.end(); _it++)
    {
        // std::cout << "in loop\n";
        std::cout << "client name ===>  " << _it->second._nickname << std::endl;
        if (_it->second._nickname == nickName && _it->first != fd)
            return (false);   
    }
    return (true);

}

bool    Commands::NICK(std::string nickName, std::map<int , Client>::iterator &_client)
{
  
    _client->second._nickname = nickName;
    std::vector<std::string> _mgs ;
    message = "\033[1m\033[32myou are known as " + nickName + RESET + "\n";
    // message.push_back("\033[1m\033[32myou are known as " + nickName + RESET + "\n");
    // _mgs += 
    send(_client->first, message.c_str(), 27 + sizeof(nickName), 0);
    // KNOWNAS(nickName.substr(0, nickName.find("\n")));
    // (void)User;
    //// check if already the nickname is used
    // User.setNickName(nickName);   
    return (true);
}



bool    Commands::USER( std::string userName, std::map<int , Client>::iterator &_client)
{
    // std::cout << " In nick fucntion " << std::endl;
    (void)userName;
    (void)_client;
    //// check if already the nickname is used
    // User.setNickName(nickName);   
    return (true);
}

bool    Commands::PASS(std::string passWord, std::map<int , Client>::iterator &_client)
{
    // std::cout << "In nick fucntion " << std::endl;
    if (_client->second._auth == REGISTERD)
    {
            message = "\033[1m\033[33m:You may not reregister\n\033[0m";
            send(_client->first, message.c_str(), 38, 0);
            // ERR_ALREADYREGISTRED;
            // RESET;
            return(false);
    }
    if (passWord != _client->second.serverPass)
    {
        message = "\033[1m\033[33m:Password incorrect\n\033[0m";
        send(_client->first, message.c_str(), 34, 0);
        return(false);
    }
    _client->second.passWord = passWord;
    _client->second._auth = REGISTERD;
    return (true);
    //// check if already the nickname is used
    // User.setNickName(nickName);   
}