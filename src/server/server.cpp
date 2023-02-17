/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:13:23 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/17 19:36:48 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
# include "../utils/ft_defines.hpp"
# include <unistd.h>
# include <netinet/in.h>
#include <arpa/inet.h>
Server::Server() : socketFd(-1), _hostname("127.0.0.1"), _port(5500)
{
    
}
Server::~Server()
{
    
}

void Server::start()
{
    /// @brief return 0 if the operation was succesfully,
    //// Otherwise, the value SOCKET_ERROR IS RETURND
    /// @brief SOCK_STREAM REFERS TO TCP SOCKET
    struct sockaddr_in adr;
    adr.sin_family = AF_INET;
    adr.sin_port = htons( _port );
    inet_aton("127.0.0.1", &adr.sin_addr);
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (socketFd == INVALID_SCOKET)
    {
        std::cout << "Socket error!" << std::endl;
        return ;
    }
    else
    {
        std::cout << " created succefully!" << std::endl;
        std::cout << "socketFd id ====> " << socketFd << std::endl;
    }
    if (bind(socketFd, (sockaddr*)&adr,sizeof(adr)) == INVALID_SCOKET)
    {
        std::cout << "Bind error!" << std::endl;
        close(socketFd);
        return ;
    }
    else
        std::cout << "Binded succefully!" << std::endl;
    close(socketFd);
    
}