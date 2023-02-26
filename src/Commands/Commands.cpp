/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:39:35 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/26 00:36:04 by zrabhi           ###   ########.fr       */
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
        REPLYPASS(cmd);
    }
    if (!cmd.compare(0, 4, "USER"))
        ERR_NEEDMOREPARAMS(cmd);
}

void    Commands::authentification(std::string &string, std::map<int, Client> _clients, int fd)
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
    std::map<int, Client>::iterator _it = _clients.find(fd); 
    if (_it->second._auth == REGISTERD && i == 2)
            ERR_ALREADYREGISTRED;
        
    (this->*_commands[i])(tmp[1], _it);
    
    // _client->second._auth = REGISTERD;
    
}


bool    Commands::validateNick(std::string &nickName, std::map<int ,Client> _user)
{
    for(std::map<int ,Client>::iterator _it = _user.begin(); _it != _user.end(); _it++)
    {
        if (!nickName.compare(_it->second._nickname))
            return (false);   
    }
    return (true);

}

bool    Commands::NICK(std::string nickName,std::map<int , Client>::iterator &_client)
{
    // std::cout << "In nick fucntion " << std::endl;
    // (void)nickName;
    // if ()
    //--- TODO: need to check nickName validity 
   
    _client->second._nickname = nickName;
    std::vector<std::string> _mgs ;
    _mgs.push_back("\033[1m\033[36m you are known as " + nickName + RESET);
    // _mgs += 
    send(_client->first, (*_mgs.begin()).c_str(), 40, 0);
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
    (void)passWord;
    (void)_client;
    _client->second.passWord = passWord;
    _client->second._auth = REGISTERD;
    return (true);
    //// check if already the nickname is used
    // User.setNickName(nickName);   
}