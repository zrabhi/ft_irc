#include "Commands.hpp"
#include "../header.hpp"

void    Commands::broadcastTopicMessage(Iterator _client, Channel &channel, String message)
{
    Vector_map users;

    FindUsersInChannel(channel.getName(), users, _client->first);
    message += " \r\n";
    for (Vector_map::iterator _it = users.begin(); _it != users.end(); _it++)
    {
        Iterator clients = _it->second.begin();
        for (; clients != _it->second.end() ; clients++)
            replyto(RPL_TOPIC(_client->second.getNickName(), _client->second.getNickName()[0], channel.getName()) + message, clients->first);
    }
}

bool    Commands::TOPIC(Vector params, Iterator &_client)
{
    if (params.size() < 3)
    {
        if (params.size() == 2 && !validateChannel(params[1]))
            return (replyto(ERR_NOSUCHCHANNEL(params[1]), _client->first) ,false);
        return (replyto(RPL_NOTOPIC(params[1]), _client->first), false);
    }
    if (!_client->second.isInChannel(params[1]))
    {
        if (!validateChannel(params[1]))
            return (replyto(ERR_NOSUCHCHANNEL(params[1]), _client->first) ,false);
        return (replyto(ERR_NOTONCHANNEL(params[1]), _client->first) ,false);
    }
    if (_client->second.getOperatorPrivilege() == CLIENT)
        return (replyto(ERR_CHANOPRIVSNEEDED(_client->second.getNickName()), _client->first), false);
    String tmp(" :");
    appendToParams(params, tmp, 2);
    ChannelMap::iterator it = _channels.find(params[1]);
    Channel& channel = it->second;
    channel.setTopic(params[2]);
    broadcastTopicMessage(_client, channel, tmp);
    return (true);
}