/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:39:35 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/23 21:19:31 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"


Commands::Commands()
{

}

Commands::~Commands()
{

}

void    Commands::checkArg(std::string &string)
{
    if(!string.compare(0, 4, "Nick") || !string.compare(0, 4, "Pass") || !string.compare(0, 4, "User")) 
        std::cout << "Command found!" << std::endl;

}

void    Commands::Nick(Client &User, std::string &nickName)
{
    (void)nickName;
    (void)User;
    //// check if already the nickname is used
    // User.setNickName(nickName);   
}