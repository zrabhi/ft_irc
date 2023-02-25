/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:39:35 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/25 02:15:49 by zrabhi           ###   ########.fr       */
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
        ERR_NEEDMOREPARAMS(cmd);
}

void    Commands::checkArg(std::string &string, std::map<int , Client>::iterator& _client)
{
    std::vector<std::string> tmp = splite(string, " ");
    makeUpper(tmp[0]);
    if (tmp.size() == 1)
    {
        commandsErrors(tmp[0]);
        return;
    }
    size_t i = 0;
    std::vector<std::string> cmdChecks ;
    cmdChecks.push_back("NICK");
    cmdChecks.push_back("PASS");
    cmdChecks.push_back("USER");
    BMemFun _commands[] = {&Commands::NICK, &Commands::PASS, &Commands::USER};
    // while (i < 3 && )
    for(i = 0;  i < 3 && tmp[0].compare(cmdChecks[i]); i++)
    {    
    }
    (this->*_commands[i])(tmp[1], _client);
    // if ()
    _client->second._auth = REGISTERD;
    // if (!tmp[0].compare(cmdChecks[i]))
    // if (!tmp[0].compare(0, 4, "NICK") || !tmp[0].compare(0, 4, "PASS") || !tmp[0].compare(0, 4, "USER")) 
    // {
    //     if (tmp.size() == 1)
    //     {
    //         if (tmp[0] == "nick")
    //             std::cout << "there are equal!" << std::endl;
    //         ERR_NONICKNAMEGIVEN;
    //         return ;
    //     }
    //     for(std::vector<std::string>::iterator _it = tmp.begin(); _it != tmp.end(); _it++)
    //     {
    //         std::cout << "parametre is " << *_it << std::endl;   
    //     }
    //     std::cout << "Command found!" << std::endl;
    // }
}
void    Commands::NICK(std::string nickName,std::map<int , Client>::iterator &_client)
{
    std::cout << " In nick fucntion 1" << std::endl;
    // (void)nickName;
    _client->second._nickname = nickName;
    // (void)User;
    //// check if already the nickname is used
    // User.setNickName(nickName);   
}



void    Commands::USER( std::string userName, std::map<int , Client>::iterator &_client)
{
    std::cout << " In nick fucntion " << std::endl;
    (void)userName;
    (void)_client;
    //// check if already the nickname is used
    // User.setNickName(nickName);   
}

void    Commands::PASS(std::string passWord, std::map<int , Client>::iterator &_client)
{
    std::cout << " In nick fucntion " << std::endl;
    (void)passWord;
    (void)_client;
    //// check if already the nickname is used
    // User.setNickName(nickName);   
}