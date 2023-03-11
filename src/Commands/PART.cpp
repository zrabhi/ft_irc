#include "Commands.hpp"
#include "../header.hpp"

void    Commands::broadcasParttMessage(Iterator _client, Channel &channel, String message)
{
    Vector_map users;

    FindUsersInChannel(channel.getName(), users, _client->first);
    if (message.size() == 2)
        message = "\r\n";
    else
    {
        message.insert(0, ":");
        message += "\r\n";
    }
    for (Vector_map::iterator _it = users.begin(); _it != users.end(); _it++)
    {
        Iterator clients = _it->second.begin();
        for (; clients != _it->second.end() ; clients++)
            replyto(REPLY_PART(_client->second.getNickName(), _client->second.getNickName()[0], channel.getName()) + message, clients->first);
    }
}

bool Commands::PART(Vector params, Iterator &_client)
{
    if (params.size() < 2)
        return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first), false);
    String tmp(" :");
    if (params.size() > 2)
        appendToParams(params, tmp, 2);
    Vector channelNames = splite(params.at(1), ",");
    for (size_t i = 0; i < channelNames.size(); i++)
    {
        String channelName = channelNames.at(i);
        if (!_client->second.isInChannel(channelNames.at(i)))
        {
            if (!validateChannel(channelName))
                return (replyto(ERR_NOSUCHCHANNEL(channelName), _client->first) ,false);
            return (replyto(ERR_NOTONCHANNEL(channelName), _client->first) ,false);
        }
        ChannelMap::iterator it = _channels.find(channelName);
        Channel& channel = it->second;
        channel.RemoveUser(_client->second);
        broadcasParttMessage(_client, channel, tmp);
    }
    return (true);
}