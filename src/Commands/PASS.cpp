#include "Commands.hpp"
#include "../header.hpp"

bool    Commands::PASS(Vector params, Iterator &_client)
{
    if (_client->second.getAuth() == REGISTERD)
        return (replyto(ERR_ALREADYREGISTRED, _client->first), false);
    if (params[1] != _client->second.getServerPass())
        return (replyto(ERR_PASSWDMISMATCH, _client->first), false);
    _client->second.setPassWord(params[1]);
    _client->second.setAuth(REGISTERD);
    return (true);
}