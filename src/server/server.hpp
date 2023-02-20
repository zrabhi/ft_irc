/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:43:26 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/20 20:49:21 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  SERVER_HPP
# define SERVER_HPP
#include <iostream>

#include "../client/client.hpp"
# include <sys/socket.h>

class Server
{
    private:
            int socketFd;
            int connection_fd;
            std::string _hostname;
            int     _port;
            fd_set  read_fds;
            fd_set  write_fds;
            fd_set  active_fds;
            int     nfds;
            // Client _client;
    public:
        Server();
        ~Server();
    void    start() ;
};

// server::server(/* args */)
// {
// }

// server::~server()
// {
// }





#endif  