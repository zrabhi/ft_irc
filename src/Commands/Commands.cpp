/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:39:35 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/24 05:40:05 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "../header.hpp"

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

void    Commands::checkArg(std::string &string)
{
    if (!string.compare(0, 4, "Nick") || !string.compare(0, 4, "Pass") || !string.compare(0, 4, "User")) 
    {
        std::vector<std::string> tmp = splite(string, " "); 
        if (tmp.size() <= 1)
        {
            ERR_NONICKNAMEGIVEN;
            return ;
        }
        for(std::vector<std::string>::iterator _it = tmp.begin(); _it != tmp.end(); _it++)
        {
            std::cout << "parametre is " << *_it << std::endl;   
        }
        std::cout << "Command found!" << std::endl;
    }
}

void    Commands::Nick(Client &User, std::string &nickName)
{
    (void)nickName;
    (void)User;
    //// check if already the nickname is used
    // User.setNickName(nickName);   
}