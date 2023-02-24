/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:12:01 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/24 00:45:39 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define    CLIENT_HPP

#include <iostream>


// server needs to know client id's thats why were creating a Client class
class Client
{
    public:
        int         _port;
        int         _fd;
        std::string _nickname;
        std::string _username;
        Client();
        
        ~Client();

        /// @brief getters 
        int     getPort() const;

        std::string getNickName() const;
      
        std::string getUserName() const;
     
        /// @brief Setters

        void  setPort(int __port);
    

        void setNickName(std::string &NickName);
     
        void   setUserName(std::string &UserName);
    

};


#endif