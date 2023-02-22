/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:13:23 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/22 21:45:11 by zrabhi           ###   ########.fr       */
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

void    disconnect()
{
    
}

void Server::start()
{
    /// @brief return 0 if the operation was succesfully,
    //// Otherwise, the value SOCKET_ERROR IS RETURND
    /// @brief SOCK_STREAM REFERS TO TCP SOCKET
    struct sockaddr_in adr; 
    int value_read;
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
        // FD_ZERO(&read_fds);
        // FD_SET(socketFd, &read_fds);
       if ((checkout = select(nfds + 1, &read_fds, &write_fds, NULL, NULL) > 0))
        {
            for (int i = 0  ; i < nfds + 1; i++) 
            {
                if (FD_ISSET(i, &read_fds)) 
                {
                    if (i == socketFd) 
                    { 
                        connection_fd = accept(socketFd,NULL, NULL);
                        if (connection_fd == INVALID_SCOKET)
                        {
                                std::cout << "Accept error!" << std::endl;
                                return ;
                        }
                        nfds = nfds >= connection_fd ? nfds : connection_fd;
                        FD_SET(connection_fd, &read_fds);
                        std::cout << "connection accepted succefully!" << std::endl;
                    }
                    value_read = read(connection_fd,  buf, 1024);
                    if (value_read <= 0)
                        std::cout << "client went away " << std::endl;
                    else
                    {
                        buf[value_read] = '\0';
                        std::cout << buf << std::endl;
                    }
                    memset(buf, 0, sizeof(buf));
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