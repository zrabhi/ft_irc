#pragma once

#include "../header.hpp"
#include <netinet/in.h>

class Server {
	private:
		int					_port;
		std::string 		_password;

		int					_sockFd;
		int					_newSocketFd;
		struct sockaddr_in	_address;

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

		void		createSocket();
		void		setSocketOptions();
		void		assignAddress2Socket();
		void		init();
} ;