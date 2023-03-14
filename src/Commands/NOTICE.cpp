# include "Commands.hpp"
# include "../header.hpp"

bool Commands::NOTICE(Vector params, Iterator &_client)
{
    Iterator reciever;
    String tmp("");
    
    if (params.size() < 3)
         return (false);
    appendToParams(params, tmp, 2);
    if (tmp == "")
        return (false);
    reciever = FindUser(params[1], _client->first);
    if (reciever == _users.end())
        return (false);
    return (replyto(NOTICE_MSG(_client->second.getNickName(), params[1], tmp),\
            reciever->first), true);
}
