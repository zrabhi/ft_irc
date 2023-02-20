/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:57:03 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/20 18:50:22 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "client.hpp"
# include "../utils/ft_defines.hpp"
# include <unistd.h>
# include <netinet/in.h>
#include <arpa/inet.h>
// initialize data memebers
Client::Client() : _port(5500), _fd(-1), _hostname("127.0.0.1"), _nickname("Client_test"),
                _username("Client"), _realname("Zac"), socketFd(-1)
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

void    Client::connected()
{
    // _hostname = hostname;
    // _port = port;
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == INVALID_SCOKET)
    {
        std::cout << "Client socket error!" << std::endl;
        return ;
    }
    std::cout << "Client socket created!" << std::endl;
    struct sockaddr_in clientAdr;
    clientAdr.sin_family = AF_INET;
    clientAdr.sin_port = htons( _port );
    inet_aton("127.0.0.1", &clientAdr.sin_addr);
    if (connect(socketFd, (sockaddr*)&clientAdr,sizeof(clientAdr)) == INVALID_SCOKET)
    {
        std::cout << "Client failed to connect!" << std::endl;
        close(socketFd);
        return ; 
    }
    std::cout << "Client Connected!" << std::endl;
    

}