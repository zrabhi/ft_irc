/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:39:35 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/25 19:12:27 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "../header.hpp"
# include <ctype.h>

Commands::Commands()
{
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
    if (!cmd.compare(0, 4, "NICK"))
        ERR_NONICKNAMEGIVEN;
    if(!cmd.compare(0, 4, "PASS"))
    {
        ERR_NEEDMOREPARAMS(cmd);
        REPLY_PASS(cmd);
    }
    if (!cmd.compare(0, 4, "USER"))
        ERR_NEEDMOREPARAMS(cmd);
}

void    Commands::authentification(std::string &string, std::map<int , Client>::iterator& _client)
{
    std::vector<std::string> tmp = splite(string, " ");
    makeUpper(tmp[0]);
    if (tmp.size() == 1)
    {   
        commandsErrors(tmp[0].substr(0, tmp[0].find("\n")));
        return;
    }
    size_t i = 0;
    std::vector<std::string> cmdChecks;
    cmdChecks.push_back("NICK");
    cmdChecks.push_back("PASS");
    cmdChecks.push_back("USER");
    BMemFun _commands[] = {&Commands::NICK, &Commands::PASS, &Commands::USER};
    for(i = 0;  i < 3 && tmp[0].compare(cmdChecks[i]); i++)
    {    
    }
    (this->*_commands[i])(tmp[1], _client);
    
    _client->second._auth = REGISTERD;
    
}
bool    Commands::NICK(std::string nickName,std::map<int , Client>::iterator &_client)
{
    std::cout << " In nick fucntion 1" << std::endl;
    // (void)nickName;
    // if ()
    //--- TODO: need to check nickName validity
    _client->second._nickname = nickName;
    KNOWNAS(nickName.substr(0, nickName.find("\n")));
    // (void)User;
    //// check if already the nickname is used
    // User.setNickName(nickName);   
    return (true);
}



bool    Commands::USER( std::string userName, std::map<int , Client>::iterator &_client)
{
    std::cout << " In nick fucntion " << std::endl;
    (void)userName;
    (void)_client;
    //// check if already the nickname is used
    // User.setNickName(nickName);   
    return (true);
}

bool    Commands::PASS(std::string passWord, std::map<int , Client>::iterator &_client)
{
    std::cout << " In nick fucntion " << std::endl;
    (void)passWord;
    (void)_client;
    return (true);
    //// check if already the nickname is used
    // User.setNickName(nickName);   
}