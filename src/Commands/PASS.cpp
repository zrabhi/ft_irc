#include "Commands.hpp"
#include "../header.hpp"

bool    Commands::PASS(Vector params, Iterator &_client)
{
    if (_client->second.getAuth() == REGISTERD)
        return (replyto(ERR_ALREADYREGISTRED, _client->first), false);
    String tmp("");
    appendToParams(params, tmp, 1);
    if (tmp != _client->second.getServerPass())
        return (std::cout << "in pass error\n", replyto(ERR_PASSWDMISMATCH, _client->first), false);
    _client->second.setPassWord(params[1]);
    _client->second.setAuth(REGISTERD);
    return (true);
}