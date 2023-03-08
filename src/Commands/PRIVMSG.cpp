#include "Commands.hpp"
# include "../header.hpp"

bool    Commands::PRIVMSG(Vector params,  Iterator &_client)
{
    if (params.size() < 3)
         return (replyto(ERR_NEEDMOREPARAMS(params[0]), _client->first),false);
    Vector_it recievers;
    Vector_map channelUsers;
    if (!checkUsers(params, recievers, channelUsers, 1, _client->first))
           return (replyto(ERR_NOSUCHNICK(params[1]), _client->first),false);
    String tmp("");
    appendToParams(params, tmp, 2);
    if (tmp == "")
        return (replyto(ERR_NOTEXTTOSEND, _client->first), false);
    for (Vector_it::iterator _it = recievers.begin(); _it != recievers.end(); _it++)
        replyto(REPLY_PIVMSG(_client->second.getNickName(), (*_it)->second.getNickName() ,\
             tmp), (*_it)->first);
    if (channelUsers.size() != 0)
    {
        for (Vector_map::iterator _it = channelUsers.begin(); _it != channelUsers.end(); _it ++)
            {
                Iterator clients = _it->second.begin();
                for (; clients != _it->second.end() ; clients++)
                {
                    if (_client->first != clients->first)
                        replyto(REPLY_PIVMSG(_client->second.getNickName(), _it->first ,tmp), clients->first);
                }
            }
    }
    std::cout << "Message is sent !" << std::endl;
    return (true);
}