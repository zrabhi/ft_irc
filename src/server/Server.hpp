#pragma once

#include "../header.hpp"
#include <netinet/in.h>
#include <fcntl.h>
#include <poll.h>

# define MAX_CLIENTS 30

class Server {
	private:
		int					_port;
		std::string 		_password;

		int					_sockFd;
		int					_newSocketFd;
		struct sockaddr_in	_address;

		struct pollfd 		_fds[MAX_CLIENTS + 1];
		int					_nfds;


		Server();
		Server(const Server& obj);
		Server& operator = (const Server& obj);

	public:
		Server( std::string port, std::string password);
		~Server();

		void		setPort( int n );
		void		setPassword( std::string password );

		int			getPort() const;
		std::string getPassword() const;

		bool		createSocket();
		bool		setSocketOptions();
		bool		editSocketmode();
		bool		assignAddress2Socket();
		bool		listenforConnections();
		void		init();
} ;