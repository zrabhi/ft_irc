/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:43:26 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/22 21:28:17 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  SERVER_HPP
# define SERVER_HPP
#include <iostream>

#include "../client/client.hpp"
# include <sys/socket.h>

typedef enum e_state{
    FREE = 0,
    BUSY = 1
} t_state;

class client_{
    public:
        int     state;      
        client_(){state = FREE;};
};

class Server
{
    private:
            int socketFd;
            int connection_fd;
            std::string _hostname;
            int         _port;
            fd_set      read_fds;
            fd_set      write_fds;
            fd_set      active_fds;
            int         nfds;
            client_     clients[1024];
            char        buf[1025];
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