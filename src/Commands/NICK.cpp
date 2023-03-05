#include "Commands.hpp"
#include "../header.hpp"


bool  Commands::NICK(Vector params, Iterator &_client)
{
    if (!validateParam(params[1], true) || params[1].size() > 9)
        return (replyto(ERR_ERRONEUSNICKNAME(params[1]), _client->first), false);
    if (_client->second.getNickName() != "" )
        KNOWNNOWAS(_client->second.getNickName(), params[1]);
    _client->second.setNickName(params[1]);
    return (true);
}