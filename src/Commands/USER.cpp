#include "Commands.hpp"
# include "../header.hpp"

bool    Commands::USER(Vector params, Iterator &_client)
{
    if (params.size() < 5)
        return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first) \
                ,replyto(REPLYUSER(params[0]), _client->first), false);
    else if (!validateUser(params[1], true))
            return (replyto(ERR_ERRONEUSNICKNAME(params[1]), _client->first), false);  
    String tmp("");
    if (params[4] == "")
        return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first)\
            ,replyto(REPLYUSER(params[0]), _client->first), false);
    appendToParams(params, tmp, 4);
    if (tmp == "")
         return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first), false);
    if (!validateUser(tmp, false))
        return (replyto(ERR_ERRONEUSNICKNAME(tmp), _client->first), false);
    return (_client->second.setUserName(params[1]),_client->second.setRealName(tmp), true);
}