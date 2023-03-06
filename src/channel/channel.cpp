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

std::string    Channel::getKey() const 
{
    return _key;
}

void    Channel::setName(const std::string& name) 
{
    _name = name;
}

void    Channel::setKey(const std::string& key) 
{
    _key = key;
}

bool Channel::checkKey(const std::string& key) const
{
    return (key == _key);
}

void Channel::addUser(Client& client, int fd)
{
    _users.insert(std::make_pair(fd, client));
    client.joinChannel(*this);
}

