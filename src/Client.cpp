/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:47:41 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/20 18:49:13 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <sys/socket.h>
 

#include "client/client.hpp"
 int main()
 {
    try
    {
        Client client;
        client.connected();
    }
    catch(...)
    {
        
    }
 }