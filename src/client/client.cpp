/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:57:03 by zrabhi            #+#    #+#             */
/*   Updated: 2023/03/14 11:28:10 by zrabhi           ###   ########.fr       */
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

Client::Client(int newFd, String _serverPass, String hostName, int port, int newStatus) :_port(port),
    _fd(newFd),
        _auth(NOT_REGISTERED),
             _status(newStatus),
                 _hostname(hostName),
                    serverPass(_serverPass),
                        passWord(""),
                            _nickname(""),
                                _username(""),
                                     _realname(""),
                                        _joinedChannels()
{
    
}

Client::~Client()
{

}

int     Client::getFd() const
{
    return _fd;
}

String Client::getNickName() const
{
    return (_nickname);
}

int Client::getAuth() const
{
    return (_auth);
}

String Client::getPassWord() const
{
    return (passWord);
}

String  Client::getRealName() const
{
    return (_realname);
}

String Client::getServerPass() const
{
    return (serverPass);
}

String Client::getUserName() const
{
    return (_username);
}

String Client::getHostName() const
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

void Client::setOperatorPrivilege(int Privilege)
{
    opreatorPrivilege = Privilege;
}

int Client::getOperatorPrivilege() const
{
    return opreatorPrivilege;
}

ChannelMap Client::getJoinedChannels() const
{
    return _joinedChannels;
}

void    Client::setNickName(String NickName)
{
    _nickname = NickName;
}


void    Client::setPort(int __port)
{
    _port = __port;
}
void    Client::setPassWord(String _password)
{
    passWord = _password;
}

void    Client::setServerPass(String _serverpass)
{
    serverPass = _serverpass;
}

void    Client::setRealName(String realName)
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

void    Client::setUserName(String UserName)
{
    _username = UserName;
}

void Client::joinChannel(Channel& channel)
{
    _joinedChannels.insert(std::make_pair(channel.getName(), channel));
}

void    Client::partFromChannel(Channel &channel)
{
    _joinedChannels.erase(channel.getName());
}

bool Client::isInChannel(String channelName)
{
    ChannelMap::iterator _it = _joinedChannels.begin();
    for(; _it !=  _joinedChannels.end(); _it++)
    {
        if (channelName == _it->first)
            return (true);
    }
    return (false);
}

