#pragma once

# include "../header.hpp"
# include "../Commands/Commands.hpp"
# include "../client/client.hpp"
#include <sys/poll.h>
#include <vector>

# define MAX_CLIENTS 30
# define NEW_CLIENT(a, b, c)   std::cout << "New client #" << a << " added from " << b << ":" << c << std::endl;

class Server {
	private:
		int					_port;
		std::string 		_password;
		int					_sockFd;
		int					_newSocketFd;
		struct sockaddr_in	_address;
		struct pollfd		_fds[MAX_CLIENTS + 1]; // todo: should be changed to a vector
		int					_nfds;
		Commands			_cmd;
		std::vector<Client> _clients;
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