#include "Commands.hpp"

bool Commands::JOIN(Vector params, Iterator &_client)
{
    if (params.size() < 2)
        return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first), false);
    
    Vector channelNames = splite(params.at(1), ",");
    Vector channelKeys;
    if (params.size() > 2)
    {
        channelKeys = splite(params.at(2), ",");
        if (channelNames.size() != channelKeys.size())
            return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first), false);
    }
    for (Vector::iterator it = channelNames.begin(); it != channelNames.end(); ++it)
    {
        String  channelName = *it;
        if (channelName.empty() || channelName[0] != '#')
            replyto(ERR_NOSUCHCHANNEL(channelName), _client->first);
    }
    for (size_t i = 0; i < channelNames.size(); i++)
    {
        String channelName = channelNames.at(i);
        String channelKey = (i < channelKeys.size()) ? channelKeys[i] : "";
        ChannelMap::iterator it = _channels.find(channelName);
        if (it == _channels.end())
        {
            Channel channel(channelName, channelKey, _client->second);
            _channels.insert(std::make_pair(channelName, channel));
        }
        else
        {
            Channel& channel = it->second;
            if (!channel.checkKey(channelKey))
                return (replyto(ERR_BADCHANNELKEY(channelName), _client->first), false);
            channel.addUser(_client->second, _client->first);
        }
    }
    ChannelMap::iterator it = _channels.begin();
    for (; it != _channels.end(); ++it)
    {
        std::cout << it->first << std::endl;
    }
    return true;
}