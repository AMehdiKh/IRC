/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:19:48 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/31 00:18:34 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

Server::Server( int port, std::string password ) : _port(port), _password(password), _creationTime(time(NULL))
{
	
}

Server::~Server( )
{
	for (ClientsMap::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
		delete it->second;
	close( this->_server_fd );
}

void	Server::initServer( void )
{
	struct sockaddr_in	addr;
	int					opt = 1;

	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->_port); // convert to network bytes order (big-endian)
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // bind the socket to all available interfaces it will listen for incoming connections on any of the machine's IP addresses

	if ( (this->_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
		throw ( std::runtime_error("Error: Unable to create server socket. Please try again!\n") );
	this->setNonBlocking(this->_server_fd);
	if ( setsockopt(this->_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0 )
		throw ( std::runtime_error("Error: Failed to set socket options. Please try again!\n") );
	if ( bind(this->_server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0 )
		throw ( std::runtime_error("Error: Unable to bind server socket. Please try again!\n") );
	if ( listen(this->_server_fd, 4096) < 0 )
		throw ( std::runtime_error("Error: Failed to listen on server socket. Please try again!\n") );
}

void	Server::setNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags < 0)
		throw std::runtime_error("Error: Failed to get file descriptor flags");
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
		throw std::runtime_error("Error: Failed to set file descriptor to non-blocking mode");
}

void	Server::removeClient( int fd )
{
	this->_kqueue.remove(fd);
	delete this->_clients[fd];
	this->_clients.erase(this->_clients.find(fd));
}

void	Server::acceptConnection( void )
{
	int					client_fd;
	struct sockaddr_in	addr;
	socklen_t			addrSize;

	addrSize = sizeof(addr);
	if ((client_fd = accept(this->_server_fd, (struct sockaddr *)&addr, &addrSize)) < 0)
		throw ( std::runtime_error("Error: Failed to accept incoming connection. Please try again!\n") );
	this->setNonBlocking(client_fd);
	this->_kqueue.add(client_fd, EV_ADD | EV_ENABLE | EV_EOF);
	this->_clients[client_fd] = new Client( client_fd, inet_ntoa(addr.sin_addr) );
}

void	Server::run( void )
{
	std::vector<struct kevent>	events;

	this->_kqueue.add(this->_server_fd, EV_ADD | EV_ENABLE);
	while (true)
	{
		events = this->_kqueue.wait();
		for (std::vector<struct kevent>::iterator event = events.begin(); event != events.end(); ++event)
		{
			if (event->ident == (uintptr_t)this->_server_fd)
				this->acceptConnection();
			else
			{
				if (event->flags & EV_EOF)
					this->removeClient( event->ident );
				else if (event->filter == EVFILT_READ)
					this->handleClient(*this->_clients[event->ident]);
			}
		}
	}
}

void	Server::handleClient( Client &client )
{
	Messages	messages = client.parseMessages(client.receive());
	
	for (Messages::iterator it(messages.begin()); it != messages.end(); ++it)
			if (handleCommands(client, it) < 0)
				break ;
}

int	Server::handleCommands(Client &client, const Messages::iterator &message)
{
	if (message->first.empty() || message->first == "CAP")
		return (0);
	else if (message->first == "PASS")
		return (this->pass(client, message->second));
	else if (message->first == "NICK")
		return (this->nick(client, message->second));
	else if (message->first == "USER")
		return (this->user(client, message->second));
	else if (message->first == "JOIN")
		return (this->join(client, message->second));
	else if (message->first == "INVITE")
		return (this->invite(client, message->second));
	else if (message->first == "MODE")
		return (this->mode(client, message->second));
	else if (message->first == "TOPIC")
		return (this->topic(client, message->second));
	else if (message->first == "KICK")
		return (this->kick(client, message->second));
	else if (message->first == "PRIVMSG" || message->first == "privmsg")
		return (this->privmsg(client, message->second));
	else
		client.reply(ERR_UNKNOWNCOMMAND(client.getNickName(), message->first) + "\r\n");
	return (0);
}

const std::string	Server::getCreationTime( void ) const
{
	struct tm	*timeinfo;
	char 		buffer[80] = {0};

	timeinfo = localtime(&this->_creationTime);
	strftime(buffer, sizeof(buffer), "%a %b %d %Y at %H:%M:%S %Z", timeinfo);

	return (buffer);
}

Client*	Server::findClientByNickname( const std::string nickName)
{
	for (ClientsMap::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
		if (it->second->getNickName() == nickName)
			return (it->second);
	return (NULL);
}

Channel*	Server::findChannel( const std::string channelName )
{
	for (ChannelsMap::iterator it = this->_channels.begin(); it != this->_channels.end(); ++it)
		if (it->first == channelName)
			return (it->second);
	return (NULL);
}
