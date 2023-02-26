#ifndef SERVER_HPP
# define SERVER_HPP

# include "../Commands/Commands.hpp"
# include "../header.hpp"
// # include "../client/client.hpp"
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
		std::vector<pollfd>	_fds;
		int					_nfds;
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
		std::map<int, Client> getClients() const;

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

#endif