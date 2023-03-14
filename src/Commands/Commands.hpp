/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:28:24 by zrabhi            #+#    #+#             */
/*   Updated: 2023/03/14 11:44:52 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <vector>
# include "../client/client.hpp"
# include "../channel/channel.hpp"
# include <map> 

class Commands
{
    public:

        typedef std::map<int , Client>                                                      Map;
        typedef std::string                                                                 String;
        typedef std::vector<String>                                                         Vector;
        typedef Map::iterator                                                               Iterator;
        typedef bool(Commands::*BMemFunGuest) (Vector param, Iterator &_client);
        typedef bool(Commands::*BMemFunClient) (Vector param, Iterator &_client);
        typedef std::vector<Iterator>                                                       Vector_it;
        typedef std::map<String, Channel>                                                   ChannelMap;
        typedef std::map<String, std::map<int, Client> >                                    Vector_map;
    
    private:
        ChannelMap  _channels;
        String      message;
        Vector      authCommands;
        Map         _users;
                               
        Iterator    FindUser(String nickName, int fd);
        
        Vector      splite(String &parametrs, String delemiter);
        
        void        countUsers(int &number);
        void        makeUpper(String &param);
        void        appendToParams(Vector params, String &tmp, size_t index);
        void        setPrivelege(Iterator &_it);
        void        NewUser(Channel &channel, Iterator _client);
        void        broadcasKickMessage(Iterator _client, Iterator User, Channel &channel, String message);
        void        broadcasParttMessage(Iterator _client, Channel &channel, String message);
        void        broadcastMessage(Iterator _client, Channel &channel);
        void        broadcastTopicMessage(Iterator _client, Channel &channel, String message);
        void        noticeClient(Iterator client, Channel channel);
        void        Welcome(String nickName, String userName, String hostName, int reciever);
        bool        FindUsersInChannel(String channelName,Vector_map &Users, int fd);
        bool        checkParams(String params);
        bool        commandsErrors(String cmd, Iterator _it, size_t index);
        bool        validateParam(String param,bool priv);
        bool        validateChannel(String channelName);
        bool        validateNick(String nickName, Map _user, int fd);
        bool        validateUserName(String userName, Map _user, int fd);
        bool        validateUser(String param, bool priv);
        bool        isSpecial(char _c);
        bool        isComma(char _c);
        bool        isHash(char _c);
        bool        isAlphaOrSpecial(char _c);
        bool        isNonWhite(char _c, bool priv);
        bool        checkUsers(Vector param, Vector_it &parameters,Vector_map &Users, size_t index, int fd);
        bool        ignoredCommands(String cmd);
        
        String      currentTime();
        
    public:
        Commands();
        ~Commands();
       
        void        WelcomeGuest(int reciever);
        void        authentification(String &string, Map &_clients, int fd);
        void        replyto(String message, int fd);
        bool        authCommandCheck(Vector params, size_t index, Iterator _it, BMemFunGuest _commands[]);
        
        bool        NICK(Vector params,  Iterator &_client);      
        bool        PASS(Vector params,  Iterator &_client);
        bool        USER(Vector params,  Iterator &_client);  
        bool        PRIVMSG(Vector params,  Iterator &_client);
        bool        JOIN(Vector params, Iterator &_client);
        bool        NOTICE(Vector params, Iterator &_client);
        bool        PART(Vector params, Iterator &_client);
        bool        KICK(Vector params, Iterator &_client);
        bool        INVITE(Vector params, Iterator &_client);
        bool        TOPIC(Vector params, Iterator &_client);
        bool        QUIT(Vector params, Iterator &_client);
        bool        BOT(Vector params, Iterator &_client);
};

typedef Commands::ChannelMap    ChannelMap;
typedef Commands::Vector        Vector;
typedef Commands::Vector_map    Vector_map;
typedef Commands::Map           Map;
typedef Commands::String        String;
typedef Commands::Iterator      Iterator;
typedef Commands::Vector_it     Vector_it;


#endif