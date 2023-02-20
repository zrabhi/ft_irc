/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:13:23 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/20 21:41:56 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
# include "../utils/ft_defines.hpp"
# include <unistd.h>
# include <netinet/in.h>
#include <arpa/inet.h>
Server::Server() : socketFd(-1), connection_fd(-1), 
        _hostname("127.0.0.1"), _port(5500)
{
    FD_ZERO(&active_fds);
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
    nfds = socketFd;
    FD_SET(socketFd, &active_fds);
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
    if (listen(socketFd, 1) == INVALID_SCOKET)
    {
        std::cout << "Listen error!" << std::endl;
        close(socketFd);        
    }
    std::cout << "succefully listening" << std::endl;     
    // close(socketFd);
    /// @brief accept returns a file descriptor for communication
    while (TRUE)
    {
        int checkout = 0;
        write_fds = read_fds = active_fds; 
        checkout = select(nfds + 1, &read_fds, &write_fds, NULL, NULL);
        if (checkout > 0)
        {
            // std::cout << "here0" << std::endl;
            for (int i = socketFd -1  ; i < nfds; i++) 
            {
                if (FD_ISSET(i, &read_fds)) 
                {
                std::cout << "in conditions\n";
                    if (i == socketFd) 
                    {
                        std::cout << "here1" << std::endl;
                        connection_fd = accept(socketFd,NULL, NULL);
                        if (connection_fd == INVALID_SCOKET)
                        {
                                std::cout << "Accept error!" << std::endl;
                                return ;
                        }
                        nfds = nfds >= connection_fd ? nfds : connection_fd;
                        FD_SET(connection_fd, &active_fds);
                        std::cout << "connection accepted succefully!" << std::endl;
                    }
                    char buf[1024];
                    std::cout << "here2" << std::endl;
                    read(connection_fd,  buf, 1024);
                    std::cout << buf << std::endl;
                }
            }
        }
        else if (checkout == INVALID_SCOKET)
        {
            // FD_CLR(&read_fds);
            // FD_CLR(&write_fds);
            // close(socketFd);
            std::cout << "Select error!"<< std::endl;
            return ;
        }
        // if(connection_fd != )
        //     {
        //         // send(Client.)
                
        //     }
    }
    // send()
    ///------client sidee-----------
    
}