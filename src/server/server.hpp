/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:43:26 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/17 18:50:07 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  SERVER_HPP
# define SERVER_HPP
#include <iostream>

# include <sys/socket.h>

class Server
{
    private:
            int socketFd;
            std::string _hostname;
            int _port;
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