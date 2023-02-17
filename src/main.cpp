/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:54:31 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/17 18:27:46 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <sys/socket.h>
 
// # include <stdio.h>
// # include <string.h>  
// # include <stdlib.h>
// # include <errno.h>
// # include <unistd.h>   
// # include <arpa/inet.h>    
// # include <sys/types.h>
// # include <sys/socket.h>
// # include <netinet/in.h>
// # include <sys/time.h>
#include "server/server.hpp"
int main(int ac, char **av)
{
    try {
         Server i_server;

         i_server.start();
    }
    catch(...)
    {
        
    }
        
}