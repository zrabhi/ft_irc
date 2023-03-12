#include "Commands.hpp"

void   Commands::NewUser(Channel &channel, Iterator _client)
{
    channel.addUser(_client->second, true);
    replyto(RFEPLY_CHANNEL(_client->second.getNickName(),_client->second.getNickName()[0], channel.getName()), _client->first);
    replyto( LISTUSERS(_client->second.getNickName(), channel.getName()) + channel.getUsersList(), _client->first);
    replyto(ENDLIST(_client->second.getNickName(), channel.getName()), _client->first);
    _channels.insert(std::make_pair(channel.getName(), channel));
}

void Commands::noticeClient(Iterator client, Channel channel)
{
    replyto(LISTUSERS(client->second.getNickName(), channel.getName()) + channel.getUsersList(), client->first);
    replyto(ENDLIST(client->second.getNickName(), channel.getName()), client->first);
}


void    Commands::broadcastMessage(Iterator _client, Channel &channel)
{
    Vector_map users;
    
    channel.addUser(_client->second, false);
    FindUsersInChannel(channel.getName(), users, _client->first);
    for (Vector_map::iterator _it = users.begin(); _it != users.end(); _it++)
    {
        Iterator clients = _it->second.begin();
        for (; clients != _it->second.end() ; clients++)
        {
            replyto(RFEPLY_CHANNEL(_client->second.getNickName(), _client->second.getNickName()[0],  _it->first), clients->first);
            if (_client->first == clients->first)
                    noticeClient(_client, channel);
        }
    }
}

bool Commands::JOIN(Vector params, Iterator &_client)
{
    if (params.size() < 2)
        return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first), false);
    Vector channelNames = splite(params.at(1), ",");
    Vector channelKeys;
    if (params.size() > 2)
        channelKeys = splite(params.at(2), ",");
    for (Vector::iterator it = channelNames.begin(); it != channelNames.end(); ++it)
    {
        if ((*it).empty() || (*it)[0] != '#')
        {
            replyto(ERR_NOSUCHCHANNEL(*it), _client->first);
            it = channelNames.erase(it);
            --it;
        }
    }
    for (size_t i = 0; i < channelNames.size(); i++)
    {
        String channelName = channelNames.at(i);
        String channelKey = (i < channelKeys.size()) ? channelKeys[i] : "";
        ChannelMap::iterator it = _channels.find(channelName);
        if (it == _channels.end())
        {
            Channel channel(channelName, channelKey, _client->second);
            NewUser(channel, _client);
        }
        else
        {
            Channel& channel = it->second;
            if (!channel.checkKey(channelKey))
                return (replyto(ERR_BADCHANNELKEY(channelName), _client->first), false);
            broadcastMessage(_client, channel);
        }
    }
    return true;
}
