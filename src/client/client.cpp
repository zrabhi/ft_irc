/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:57:03 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/27 21:07:50 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "client.hpp"
#include "../header.hpp"

// initialize data memebers
Client::Client() : _port(), 
                _fd(-1), 
                _auth(NOT_REGISTERED),
                _status(GUEST),
                _hostname(""),
                passWord(""),
                _nickname(""),
                _username(),
                _realname()
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