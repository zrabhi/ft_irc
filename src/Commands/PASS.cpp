#include "Commands.hpp"
#include "../header.hpp"

bool    Commands::PASS(Vector params, Iterator &_client)
{
    if (_client->second.getAuth() == REGISTERD)
    {
        replyto(ERR_ALREADYREGISTRED, _client->first);
        return(false);
    }
    if (params[1] != _client->second.getServerPass())
    {
        replyto(ERR_PASSWDMISMATCH, _client->first);
        return(false);
    }
    _client->second.setPassWord(params[1]);
    _client->second.setAuth(REGISTERD);
    return (true);
}