/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:57:03 by zrabhi            #+#    #+#             */
/*   Updated: 2023/03/07 23:53:32 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "client.hpp"
#include "../header.hpp"
#include "../channel/channel.hpp"
#include <utility>

// initialize data memebers
Client::Client() : _port(), 
    _fd(-1), 
        _auth(NOT_REGISTERED),
            _status(GUEST),
                _hostname(""),
                    passWord(""),
                        _nickname(""),
                            _username(""),
                                _realname("")
{

}

Client::Client(int newFd, std::string _serverPass, std::string hostName, int port, int newStatus) :_port(port),
    _fd(newFd),
        _auth(NOT_REGISTERED),
             _status(newStatus),
                 _hostname(hostName),
                    serverPass(_serverPass),
                        passWord(""),
                            _nickname(""),
                                _username(""),
                                     _realname("")
{
    
}

Client::~Client()
{

}

int     Client::getFd() const
{
    return _fd;
}

std::string Client::getNickName() const
{
    return (_nickname);
}

int Client::getAuth() const
{
    return (_auth);
}

std::string Client::getPassWord() const
{
    return (passWord);
}

std::string  Client::getRealName() const
{
    return (_realname);
}

std::string Client::getServerPass() const
{
    return (serverPass);
}

std::string Client::getUserName() const
{
    return (_username);
}

std::string Client::getHostName() const
{
    return (_hostname);
}

int Client::getStatus() const
{
    return (_status);
}

int Client::getPort() const
{
    return (_port);
}

void    Client::setNickName(std::string NickName)
{
    _nickname = NickName;
}


void    Client::setPort(int __port)
{
    _port = __port;
}
void    Client::setPassWord(std::string _password)
{
    passWord = _password;
}

void    Client::setServerPass(std::string _serverpass)
{
    serverPass = _serverpass;
}

void    Client::setRealName(std::string realName)
{
    _realname = realName;
}

void    Client::setFd(int newFd)
{
    _fd = newFd;
}

void    Client::setAuth(int newAuth)
{
    _auth = newAuth;
}

void   Client::setStatus(int newStatus)
{
    _status = newStatus;
}

void    Client::setUserName(std::string UserName)
{
    _username = UserName;
}

void Client::joinChannel(Channel& channel)
{
    _joinedChannels.insert(std::make_pair(channel.getName(), channel));
}

