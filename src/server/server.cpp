# include "../Commands/Commands.hpp"
#include "server.hpp"
#include <sys/_types/_size_t.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <vector>
// #include "../header.hpp"

Server::Server( String port, String password) 
{
	if (atoi(port.c_str()) < 1024 || atoi(port.c_str()) > 65536)
		throw std::runtime_error("Port number should be between 1025 and 65536");
	_port = atoi(port.c_str());
	_password = password;
}

Server::~Server()
{

}

void	Server::setPort( int n ) 
{ 
	_port = n; 
}

void	Server::setPassword( String password )
{
	_password = password; 
}

int		Server::getPort() const 
{ 
	return _port;
} 

Map Server::getClients() const 
{ 
	return _clients; 
}
String Server::getPassword() const 
{ 
	return _password; 
}

bool	Server::createSocket() 
{
	_serverFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_serverFd == -1)
	{
		std::cerr << "socket() failed: " << strerror(errno) << std::endl;
		return false;
	}
	return true;
}

bool	Server::setSocketOptions()
{
	int optionvalue = 1;
	if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR,
		&optionvalue, sizeof(optionvalue)) == -1)
	{
		std::cerr << "setsockopt() failed: " << strerror(errno) << std::endl;
		close(_serverFd);
		return false;
	}
	return true;
}

bool	Server::editSocketmode()
{
	if (fcntl(_serverFd, F_SETFL, O_NONBLOCK) == -1)
	{
			std::cerr << "fcntl() failed: " << strerror(errno) << std::endl;
		close(_serverFd);
		return false;
	}
	return true;
}

bool	Server::assignAddress2Socket()
{
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(_port);
	if (bind(_serverFd, (struct sockaddr*)&_address, sizeof(_address)) == -1)
	{
		std::cerr << "bind() failed: " << strerror(errno) << std::endl;
		close(_serverFd);
		return false;
	}
	return true;
}

bool	Server::listenforConnections()
{
	if (listen(_serverFd, SIMULTANEOUS_CONNECTIONS) == -1)
	{
		std::cerr << "listen() failed: " << strerror(errno) << std::endl;
		close(_serverFd);
		return false;
	}
	return true;
}

bool	Server::monitorEvents()
{
	if (poll(&_fds[0], _fds.size(), -1) == -1)
	{
		std::cerr << "poll() failed: " << strerror(errno) << std::endl;
		close(_serverFd);
		return false;
	}
	return true;
}

bool	Server::acceptNewConnection()
{
	int addrlen = sizeof(_address);
	_newSocketFd = accept(_serverFd, (struct sockaddr*) &_address, (socklen_t*)&addrlen);
	if (_newSocketFd == -1) 
	{
		std::cerr << "accept() failed: " << strerror(errno) << std::endl;
		close(_serverFd);
		return false;
	}
	return true;
}

void	Server::addClientSockettoFdSet() 
{
	_cmd.WelcomeGuest(_newSocketFd);
	Client _new_client(_newSocketFd, _password, inet_ntoa(_address.sin_addr),\
			ntohs(_address.sin_port) , GUEST);
	_new_client._buffer = "";
	struct pollfd newGuestFd;
	newGuestFd.fd = _newSocketFd;
	newGuestFd.events = POLLIN;
	_fds.push_back(newGuestFd);
	_clients.insert(std::make_pair(_newSocketFd, _new_client));
}

bool	Server::incomingConnectionRequest()
{
    if (_fds.at(0).revents & POLLIN)
	{
		if (!acceptNewConnection())
			return false;
		addClientSockettoFdSet();
	}
	return true;
}

void Server::incomingClientData()
{
    for (size_t i = 1; i < _fds.size(); i++)
    {   
        if (_fds.at(i).revents & POLLIN)
        {
            char buffer[1024] = {0};
            int result = recv(_fds.at(i).fd, &buffer, sizeof(buffer), 0);
            if (result > 0)
                _clients.at(_fds.at(i).fd)._buffer += String(buffer, result);
            size_t pos = _clients.at(_fds.at(i).fd)._buffer.find_first_of("\r\n");
            while (pos != String::npos)
            {
                String msg = _clients.at(_fds.at(i).fd)._buffer.substr(0, pos);
                _clients.at(_fds.at(i).fd)._buffer = _clients.at(_fds.at(i).fd)._buffer.substr(pos + 1);
                if (!msg.empty())
                    _cmd.authentification(msg, _clients, _fds[i].fd);
                pos = _clients[_fds[i].fd]._buffer.find_first_of("\r\n");
            }
            if (result == 0)
            {
				String name = _clients[_fds.at(i).fd].getNickName();
				if (name.empty())
	                std::cout << "Guest Left" << std::endl;
				else
	                std::cout << name << " Left" << std::endl;
                _clients.at(_fds.at(i).fd)._buffer.clear();
                _clients.erase(_fds.at(i).fd);
                close(_fds.at(i).fd);
                _fds.erase(_fds.begin() + i);
                i--;
            } 
            else if (result == -1) 
            {
                if (errno != EWOULDBLOCK)
                {
                    close(_fds.at(i).fd);
                    _fds.erase(_fds.begin() + i);
                }
            }
        }
    }
}

void	Server::init()
{
	if (!createSocket() || !setSocketOptions() || !editSocketmode()
		|| !assignAddress2Socket() || !listenforConnections())
			return ;
	struct pollfd	tmp;
	tmp.fd = _serverFd;
	tmp.events = POLLIN;
	_fds.push_back(tmp);
	while (true)
	{
		if (!monitorEvents() || !incomingConnectionRequest())
			break ;
		incomingClientData();
	}
}
