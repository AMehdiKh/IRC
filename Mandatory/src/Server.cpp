/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:19:48 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/19 09:27:25 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include <locale>
#include <map>
#include <string>
#include <sys/socket.h>
#include <vector>

Server::Server( int port, std::string password ) : _port(port), _password(password)
{
	
}

Server::~Server( )
{
	std::map<int, Client*>::iterator	it;
	close( this->_server_fd );
	for (it = this->_clients.begin(); it != this->_clients.end(); ++it)
		delete it->second;
		
}

void	Server::initServer( void )
{
	struct sockaddr_in	addr;
	int					opt = 1;

	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->_port); // convert to network bytes order (big-endian)
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // bind the socket to all available interfaces it will listen for incoming connections on any of the machine's IP addresses

	if ( (this->_server_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) < 0 )
		throw ( std::runtime_error("Error: Unable to create server socket. Please try again!\n") );
	if ( setsockopt(this->_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0 )
		throw ( std::runtime_error("Error: Failed to set socket options. Please try again!\n") );
	if ( bind(this->_server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0 )
		throw ( std::runtime_error("Error: Unable to bind server socket. Please try again!\n") );
	if ( listen(this->_server_fd, 4096) < 0 )
		throw ( std::runtime_error("Error: Failed to listen on server socket. Please try again!\n") );
}

void	Server::run( void )
{
	std::vector<struct epoll_event>	events;

	this->_epoll.add(this->_server_fd, EPOLLIN);
	while (true)
	{
		events = this->_epoll.wait();
		for (std::vector<struct epoll_event>::iterator event = events.begin(); event != events.end(); ++event)
		{
			if (event->data.fd == this->_server_fd)
				this->acceptConnection();
			else
			{
				if (event->events & (EPOLLRDHUP | EPOLLHUP))
				{
					this->_epoll.remove( event->data.fd );
					this->removeClient( event->data.fd );
				}
				else
				{
					char	messageBuffer[BUFFER_SIZE] = { 0 };

					if (recv(event->data.fd, messageBuffer, sizeof(messageBuffer), 0) < 0)
						if (errno != EAGAIN && errno != EWOULDBLOCK)
							throw ( std::runtime_error("Error: Failed to receive data. Please try again!\n") );
					// std::cout << messageBuffer << "######[end]######\n";
					this->_clients[event->data.fd]->parseMessages(messageBuffer);
					this->handleCommands(*this->_clients[event->data.fd]);
				}
			}
		}
	}
}

void	Server::handleCommands( const Client &client )
{
	Messages	messages(client.getMessages());
	
	for (Messages::iterator it(messages.begin()); it != messages.end(); ++it)
	{
		if (it->first == "CAP")
			continue;
		else if (it->first == "PASS")
			this->pass(client);
		else if (it->first == "NICK")
			this->nick(client);
		else if (it->first == "USER")
			this->user(client);
		else
			// sent error ERR_UNKNOWNCOMMAND (421) unknown command
	}
}

void	Server::pass( const Client &client )
{
	
}

void	Server::removeClient( int fd )
{
	delete this->_clients[fd];
	this->_clients.erase(this->_clients.find(fd));
}

void	Server::acceptConnection( void )
{
	int					client_fd;
	struct sockaddr_in	addr;
	socklen_t			addrSize;

	addrSize = sizeof(addr);
	if ((client_fd = accept4(this->_server_fd, (struct sockaddr *)&addr, &addrSize, SOCK_NONBLOCK)) < 0)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK)
			throw ( std::runtime_error("Error: Failed to accept incoming connection. Please try again!\n") );
		return ;
	}
	this->_epoll.add(client_fd, EPOLLIN | EPOLLRDHUP | EPOLLHUP);
	this->_clients[client_fd] = new Client( client_fd, inet_ntoa(addr.sin_addr) );
}
