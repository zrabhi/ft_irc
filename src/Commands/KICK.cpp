#include "Commands.hpp"
#include "../header.hpp"


void    Commands::broadcasKickMessage(Iterator _client, Iterator User, Channel &channel)
{
    Vector_map users;

    FindUsersInChannel(channel.getName(), users, _client->first);
    for (Vector_map::iterator _it = users.begin(); _it != users.end(); _it++)
    {
        Iterator clients = _it->second.begin();
        for (; clients != _it->second.end() ; clients++)
            replyto(REPLY_KICK(_client->second.getNickName(), channel.getName(),\
                 User->second.getNickName()), clients->first);
    }
}

bool Commands::KICK(Vector params, Iterator &_client)
{
    if (params.size() < 3)
        return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first), false);
    Iterator User;
    if (_client->second.getOperatorPrivilege() == CLIENT)
        return (replyto(ERR_CHANOPRIVSNEEDED(params[2]), _client->first), false);
    if ((User = FindUser(params[2], _client->first)) == _users.end())
            return (replyto(ERR_NOSUCHNICK(params[2]), _client->first), false);        
    else if (!validateChannel(params[1]))
        return (replyto(ERR_NOSUCHCHANNEL(params[1]), _client->first) ,false);
    else if (!_client->second.isInChannel(params[2]))
        return (replyto(ERR_NOTONCHANNEL(params[2]), _client->first) ,false);
    else 
    {
        ChannelMap::iterator it = _channels.find(params[1]);
        Channel& channel = it->second;
        channel.RemoveUser(User->second);
        broadcasKickMessage(_client, User, channel);
    }
    return (true);
}