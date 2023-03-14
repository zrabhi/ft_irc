#ifndef SERVER_HPP
# define SERVER_HPP

# include "../Commands/Commands.hpp"
# include "../header.hpp"
// # include "../client/client.hpp"
#include <sys/poll.h>
#include <map>

# define SIMULTANEOUS_CONNECTIONS 30

class Server {

	public:
		
		typedef std::string          		String;
		typedef std::map<int , Client>    	Map;
		typedef	std::vector<pollfd>         VectorFDS;
	
	private:
		int					  _port;
		String 		  	      _password;
		int					  _serverFd;
		int					  _newSocketFd;
		struct sockaddr_in	  _address;
		VectorFDS	  	      _fds;
		Commands			  _cmd;
		Map 				  _clients;

		Server();
		Server(const Server& obj);
		Server& operator = (const Server& obj);

	public:
		Server( String port, String password);
		~Server();
		
		void		setPort( int n );
		void		setPassword( String password );

		int			getPort() const;
		String 		getPassword() const;
		Map 		getClients() const;

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

typedef Server::Map          	Map;
typedef Server::String        	String;
typedef	Server::VectorFDS       VectorFDS;

#endif