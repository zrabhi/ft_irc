                                                                                           /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:12:01 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/25 00:58:57 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define    CLIENT_HPP

#include <iostream>
#include <vector>
#include <map>

class Channel;

class Client
{
    private:
        int                         _port;
        int                         _fd;
        int                         _auth;
        int                         _status;
        std::string                 _hostname;
        std::string                 serverPass;         
        std::string                 passWord;
        std::string                 _nickname;
        std::string                 _username;
        std::string                 _realname;
        std::vector<std::string>    _joinedChannels;
        // std::map<std::string, Channel>    _joinedChannels;
        
    public:
        Client();
        Client(int newFd, std::string _serverPass, std::string hostName, int port, int newStatus);
        ~Client();

        /// @brief getters 
        int         getPort() const;
        int         getAuth()  const;
        int         getStatus() const;
        int         getFd() const;
        std::string getPassWord() const;
        std::string getHostName() const;
        std::string getServerPass() const;
        std::string getRealName()   const;
        std::string getNickName() const;
        std::string getUserName() const;
        std::vector<std::string> getJoinedChannels() const;
     
        /// @brief Setters

        void   setPort(int __port);
        void   setNickName(std::string NickName);
        void   setPassWord(std::string _password);
        void   setServerPass(std::string _serverpass);
        void   setAuth(int newAuth);
        void   setStatus(int newStatus);
        void   setFd(int newFd);
        void   setRealName(std::string realName);
        void   setUserName(std::string UserName);

        void    joinChannel(std::string channelName);

};


#endif