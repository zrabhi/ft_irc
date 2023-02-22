#include "Server.hpp"
#include <cstring>
#include <netinet/in.h>
#include <sys/_endian.h>
#include <sys/_types/_socklen_t.h>
#include <sys/socket.h>
#include <fcntl.h>

Server::Server( std::string port, std::string password) {
	if (atoi(port.c_str()) < 1024 || atoi(port.c_str()) > 65536)
		throw std::runtime_error("Port number should be between 1025 and 65536");
	_port = atoi(port.c_str());
	_password = password;
}

Server::~Server() {}

void	Server::setPort( int n ) { _port = n; }

void	Server::setPassword( std::string password ) { _password = password; }

int		Server::getPort() const { return _port; }

std::string Server::getPassword() const { return _password; }

void		Server::init() {
	_sockFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_sockFd == -1) {
		std::cerr << "socket() failed: " << strerror(errno) << std::endl;
		return ;
	}

	int optionvalue = 1;
	if (setsockopt(_sockFd, SOL_SOCKET, SO_REUSEADDR,
		&optionvalue, sizeof(optionvalue)) == -1) {
		std::cerr << "setsockopt() failed: " << strerror(errno) << std::endl;
		close(_sockFd);
		return ;
	}

	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(_port);

	if (bind(_sockFd, (struct sockaddr*)&_address, sizeof(_address)) == -1) {
		std::cerr << "bind() failed: " << strerror(errno) << std::endl;
		close(_sockFd);
		return ;
	}

	if (listen(_sockFd, 3) == -1) {
		std::cerr << "listen() failed: " << strerror(errno) << std::endl;
		close(_sockFd);
		return ;
	}

	int addrlen = sizeof(_address);
	_newSocketFd = accept(_sockFd, (struct sockaddr*)&_address, (socklen_t*)&addrlen);
	if (_newSocketFd == -1) {
		std::cerr << "accept() failed: " << strerror(errno) << std::endl;
		close(_sockFd);
		return ;
	}

	char buffer[1024] = {0};
	while (1) {
		recv(_newSocketFd, &buffer, sizeof(buffer), 0);
		if (buffer[0] == 0)
			return;
		send(_newSocketFd, "server says hi\n", sizeof("server says hi\n"), 0);
    	std::cout << buffer;
		memset(buffer, 0, sizeof(buffer));
	}
    close(_newSocketFd);
	close(_sockFd);
}
