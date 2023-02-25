#pragma once

# include "../header.hpp"
# include "../Commands/Commands.hpp"
# include "../client/client.hpp"
#include <sys/poll.h>
#include <map>

# define SIMULTANEOUS_CONNECTIONS 30
# define NEW_CLIENT(a, b, c)   std::cout << "New client #" << a << " added from " << b << ":" << c << std::endl;

class Server {
	private:
		int					_port;
		std::string 		_password;
		int					_serverFd;
		int					_newSocketFd;
		struct sockaddr_in	_address;
		// struct pollfd		_fds[MAX_CLIENTS + 1]; // todo: should be changed to a vector
		std::vector<pollfd>	_fds1;
		int					_nfds;
		std::vector<pollfd> _fds1;
		Commands			_cmd;
		std::map<int, Client> _clients;
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
		bool		monitorEvents();
		bool		acceptNewConnection();
		bool		incomingConnectionRequest();
		void		incomingClientData();
		void		addClientSockettoFdSet();
		void		init();
} ;