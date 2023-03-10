/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:28:24 by zrabhi            #+#    #+#             */
/*   Updated: 2023/03/10 02:53:13 by zrabhi           ###   ########.fr       */
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
        typedef std::vector<Iterator>                   Vector_it;
        typedef std::map<String, Channel>                                                   ChannelMap;
        typedef std::map<String, std::map<int, Client> >                                    Vector_map;
    
    private:
        Map         _users;
        Vector      authCommands;
        ChannelMap  _channels;
        String      message;
                               
        bool        commandsErrors(String cmd, Iterator _it, size_t index);
       
        Vector      splite(String &parametrs, String delemiter);
        void        makeUpper(String &param);
        void        appendToParams(Vector params, String &tmp, size_t index);
        Iterator    FindUser(String nickName, int fd);
        bool        FindUsersInChannel(String channelName,Vector_map &Users, int fd);
        bool        checkParams(String params);
        void        setPrivelege(Iterator &_it);
        
        void        NewUser(Channel &channel, Iterator _client);
        void        noticeClient(Iterator client, Channel channel);
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
        String      currentTime();
   
        void        broadcasKickMessage(Iterator _client, Iterator User, Channel &channel);
        void        broadcasParttMessage(Iterator _client, Channel &channel);
        void        broadcastMessage(Iterator _client, Channel &channel);
    public:
        Commands();
        ~Commands();
       
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
};

typedef Commands::ChannelMap ChannelMap;
typedef Commands::Vector    Vector;
typedef Commands::Vector_map    Vector_map;
typedef Commands::Map       Map;
typedef Commands::String    String;
typedef Commands::Iterator  Iterator;
typedef Commands::Vector_it  Vector_it;


#endif