/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:57:03 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/15 22:30:08 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "client.hpp"

// initialize data memebers
Client::Client()
{

}

Client::~Client()
{

}

std::string Client::getNickName() const
{
    return (_nickname);
}

std::string Client::getUserName() const
{
    return (_username);
}

int Client::getPort() const
{
    return (_port);
}

void    Client::setNickName(std::string &NickName)
{
    _nickname = NickName;
}

void    Client::setPort(int __port)
{
    _port = __port;
}

void    Client::setUserName(std::string &UserName)
{
    _username = UserName;
}