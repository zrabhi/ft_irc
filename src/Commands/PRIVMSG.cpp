#include "Commands.hpp"
# include "../header.hpp"

bool    Commands::PRIVMSG(Vector params,  Iterator &_client)
{
    if (params.size() < 3)
         return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first),false);
    Vector_it recievers;
    if (!checkUsers(params, recievers, 1, _client->first))
           return (replyto(ERR_NOSUCHNICK(params[1]), _client->first),false);
    else
        {
            String tmp("");
            params[params.size() - 1] = params[params.size() -1].\
            substr(0, params[params.size() -1].find("\n"));
            appendToParams(params, tmp, 2);
            if (tmp == "")
                return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first), false);
            tmp += "\n";
            for(Vector_it::iterator _it = recievers.begin(); _it != recievers.end(); _it++)
                        replyto(tmp, (*_it)->first);
            std::cout << "Message is sent !" << std::endl;
        }
    return (true);
}