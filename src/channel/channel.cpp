#include "channel.hpp"
#include <utility>

Channel::Channel() :
_name(""), _topic(""), _key("")
{}

Channel::Channel(std::string name, std::string key, Client creator) : 
_name(name), _topic(""), _key(key), _creator(creator)
{
}

Channel::~Channel() 
{

}

std::string    Channel::getName() const 
{
    return _name;
}

std::string     Channel::getUsersList() const
{
    std::string list = ":";

    std::map<int, Client>::const_iterator iter = _users.begin();
    for (; iter != _users.end(); iter++)
    {
        if (iter->second.getNickName() == _creator.getNickName())
                list += "@" + iter->second.getNickName() + " ";
        else
            list += iter->second.getNickName() + " ";
    }
    list += "\r\n";
    return (list);
}

std::map<int, Client> Channel::getUsers()  const
{
    return _users;
}

std::string    Channel::getKey() const 
{
    return _key;
}

void    Channel::setName(const std::string& name) 
{
    _name = name;
}

void    Channel::setTopic(const std::string topic)
{
    _topic = topic;
}

std::string Channel::geTopic() const
{
    return _topic;
}

void    Channel::setKey(const std::string& key) 
{
    _key = key;
}


bool Channel::checkKey(const std::string& key) const
{
    return (key == _key);
}

void Channel::addUser(Client& client, bool PrivilegeSetter)
{
    _users.insert(std::make_pair(client.getFd(), client));
    client.joinChannel(*this);
    if (PrivilegeSetter)
        client.setOperatorPrivilege(O);
    else 
        client.setOperatorPrivilege(CLIENT);
}

void    Channel::RemoveUser(Client &client)
{
    _users.erase(client.getFd());  
    client.partFromChannel(*this);
}

