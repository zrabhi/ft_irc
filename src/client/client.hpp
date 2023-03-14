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
    public:
        typedef std::string                     String;
        typedef std::map<String, Channel>       ChannelMap;
    private:
        
        int                  _port;
        int                  _fd;
        int                  _auth;
        int                  _status;
        int                  opreatorPrivilege;
        String               _hostname;
        String               serverPass;         
        String               passWord;
        String               _nickname;
        String               _username;
        String               _realname;
        ChannelMap           _joinedChannels;
        
        
    public:
        String  _buffer;

        Client();
        Client(int newFd, String _serverPass, String hostName, int port, int newStatus);
        ~Client();

        /// @brief getters 
        int         getPort() const;
        int         getAuth()  const;
        int         getStatus() const;
        int         getFd() const;
        int         getOperatorPrivilege() const;
        String      getPassWord() const;
        String      getHostName() const;
        String      getServerPass() const;
        String      getRealName()   const;
        String      getNickName() const;
        String      getUserName() const;

        ChannelMap  getJoinedChannels() const;
     
        /// @brief Setters
        bool        isInChannel(String channelName);

        
        void        setPort(int __port);
        void        setNickName(String NickName);
        void        setPassWord(String _password);
        void        setServerPass(String _serverpass);
        void        setAuth(int newAuth);
        void        setStatus(int newStatus);
        void        setFd(int newFd);
        void        setRealName(String realName);
        void        setUserName(String UserName);
        void        setOperatorPrivilege(int Privilege);
        void        partFromChannel(Channel &channel);
        void        joinChannel(Channel& channel);

};

typedef Client::String      String;
typedef Client::ChannelMap  ChannelMap;
#endif