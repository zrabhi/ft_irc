#include "Server.hpp"
#include <ostream>

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

	if (listen(_sockFd, MAX_CLIENTS) == -1) {
		std::cerr << "listen() failed: " << strerror(errno) << std::endl;
		close(_sockFd);
		return ;
	}

	_fds[0].fd = _sockFd;
	_fds[0].events = POLLIN;

	_nfds = 1;
	for ( ; ; ) {
    	if (poll(_fds, _nfds, -1) == -1) {
    	    std::cerr << "poll() failed: " << strerror(errno) << std::endl;
    	    close(_sockFd);
    	    return ;
    	}

    	// Check if there is incoming connection request
    	if (_fds[0].revents & POLLIN) {
    	    // Accept the new connection
    	    int addrlen = sizeof(_address);
    	    _newSocketFd = accept(_sockFd, (struct sockaddr*)&_address, (socklen_t*)&addrlen);
    	    if (_newSocketFd == -1) {
    	        std::cerr << "accept() failed: " << strerror(errno) << std::endl;
    	        close(_sockFd);
    	        return ;
    	    }
    	    // Add the new client socket to the poll set
    	    if (_nfds >= MAX_CLIENTS + 1) {
    	        std::cerr << "Too many clients, rejecting connection" << std::endl;
    	        close(_newSocketFd);
    	    } else {
    	        _fds[_nfds].fd = _newSocketFd;
    	        _fds[_nfds].events = POLLIN;
				std::cout << "Welcome " << _nfds << std::endl;
    	        _nfds++;
    	    }
    	}

    	// Check all client sockets for incoming data
    	for (int i = 1; i < _nfds; i++) {
    	    if (_fds[i].revents & POLLIN) {
    	        char buffer[1024] = {0};
    	        int result = recv(_fds[i].fd, &buffer, sizeof(buffer), 0);
				if (buffer[0])
					std::cout << "Client " << i << " says " << buffer << std::flush; 
    	        if (result == 0) {
    	            // Connection closed by the client
					std::cout << "Client " << i << " Left" << std::endl;
    	            close(_fds[i].fd);
    	            _fds[i] = _fds[_nfds - 1];
    	            _nfds--;
    	            i--;
    	        } else if (result == -1) {
    	            // Error on the socket
    	            std::cerr << "recv() failed: " << strerror(errno) << std::endl;
    	            close(_fds[i].fd);
    	            _fds[i] = _fds[_nfds];
				}
			}
		}
	}
}
