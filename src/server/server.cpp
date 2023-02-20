#include "Server.hpp"
#include <cstring>
#include <netinet/in.h>
#include <sys/_endian.h>
#include <sys/_types/_socklen_t.h>
#include <sys/socket.h>

// # define SERVER_FAILED 

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
	int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd == -1) {
		std::cerr << "socket() failed: " << strerror(errno) << std::endl;
		return ;
	}

	int option = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT,
		&option, sizeof(option)) == -1) {
		std::cerr << "setsockopt() failed: " << strerror(errno) << std::endl;
		close(sockfd);
		return ;
	}

	struct	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(_port);

	if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) == -1) {
		std::cerr << "bind() failed: " << strerror(errno) << std::endl;
		close(sockfd);
		return ;
	}

	if (listen(sockfd, 3) == -1) {
		std::cerr << "listen() failed: " << strerror(errno) << std::endl;
		close(sockfd);
		return ;
	}

	int addrlen = sizeof(address);
	int newSocket = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
	if (newSocket == -1) {
		std::cerr << "accept() failed: " << strerror(errno) << std::endl;
		close(sockfd);
		return ;
	}

	char buffer[1024] = {0};
	while (1) {
		recv(newSocket, &buffer, sizeof(buffer), 0);
		
		send(newSocket, "server says hi\n", sizeof("server says hi\n"), 0);
    	std::cout << buffer;
		if (buffer[0] == 0)
			break;
		memset(buffer, 0, sizeof(buffer));
	}
    close(newSocket);
}
