#pragma once

#include "../header.hpp"

class Server {
	private:
		int			_port;
		std::string _password;

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

		void		init();
} ;