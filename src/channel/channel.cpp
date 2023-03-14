#include "channel.hpp"
#include <utility>

Channel::Channel() :
_name(""), _topic(""), _key("")
{}

Channel::Channel(String name, String key, Client creator) : 
_name(name), _topic(""), _key(key), _creator(creator)
{
}

Channel::~Channel() 
{

}

String    Channel::getName() const 
{
    return _name;
}

String     Channel::getUsersList() const
{
    String list = ":";

    Map::const_iterator iter = _users.begin();
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

Map Channel::getUsers()  const
{
    return _users;
}

String    Channel::getKey() const 
{
    return _key;
}

void    Channel::setName(const String& name) 
{
    _name = name;
}

void    Channel::setTopic(const String topic)
{
    _topic = topic;
}

String Channel::geTopic() const
{
    return _topic;
}

void    Channel::setKey(const String& key) 
{
    _key = key;
}


bool Channel::checkKey(const String& key) const
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

