/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:19:48 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/28 08:55:19 by codespace        ###   ########.fr       */
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

	if ( (this->_server_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) < 0 )
		throw ( std::runtime_error("Error: Unable to create server socket. Please try again!\n") );
	if ( setsockopt(this->_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0 )
		throw ( std::runtime_error("Error: Failed to set socket options. Please try again!\n") );
	if ( bind(this->_server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0 )
		throw ( std::runtime_error("Error: Unable to bind server socket. Please try again!\n") );
	if ( listen(this->_server_fd, 4096) < 0 )
		throw ( std::runtime_error("Error: Failed to listen on server socket. Please try again!\n") );
}


void	Server::removeClient( int fd )
{
	this->_epoll.remove(fd);
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
					this->removeClient( event->data.fd );
				else
					this->handleClient(*this->_clients[event->data.fd]);
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
	else
		client.reply(ERR_UNKNOWNCOMMAND(client.getNickName(), message->first) + "\r\n");
	return (0);
}

int	Server::checkNickNameForm( const std::string &nickName )
{
	if (nickName.size() > 9)
		return (-1);
	if (nickName.at(0) == '#' || nickName.at(0) == ':' || nickName.at(0) == '$')
		return (-1);
	if (nickName.find_first_of(" .,*?!@") != std::string::npos)
		return (-1);
	return (0);
}

int	Server::checkNickNameInUse( const std::string &nickName )
{
	for (ClientsMap::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
		if (it->second->getNickName() == nickName)
			return (-1);
	return (0);			
}


int	Server::user( Client &client, const std::vector<std::string> &parameters )
{
	if (client.getClientState() == UNREGISTERED)
		return (0);
	if (client.getClientState() == REGISTERED)
		return (client.reply(ERR_ALREADYREGISTERED(client.getNickName()) + "\r\n"), 0);
	if (parameters.size() < 4)
		return (client.reply(ERR_NEEDMOREPARAMS(client.getNickName(), "USER") + "\r\n"), 0);
	client.setUserName(parameters.at(0));
	client.setrealName(parameters.at(3));
	client.welcome(this->getCreationTime());
	return (0);
}

int	Server::nick( Client &client, const std::vector<std::string> &parameters )
{
	if (client.getClientState() == UNREGISTERED)
		return (0);
	if (parameters.empty() || parameters.at(0).empty())
		return (client.reply(ERR_NONICKNAMEGIVEN(client.getNickName()) + "\r\n"), 0);
	if (this->checkNickNameForm(parameters.at(0)) < 0)
		return (client.reply(ERR_ERRONEUSNICKNAME(client.getNickName(), parameters.at(0)) + "\r\n"), 0);
	if (client.getNickName() == parameters.at(0))
		return (0);
	if (this->checkNickNameInUse(parameters.at(0)) < 0)
		return (client.reply(ERR_NICKNAMEINUSE(client.getNickName(), parameters.at(0)) + "\r\n"), 0);
	if (client.getClientState() == REGISTERED)
		client.reply(RPL_NICK(client.getPrefix(), parameters.at(0)) + "\r\n");
	client.setNickName(parameters.at(0));
	if (client.getClientState() != REGISTERED)
		client.welcome(this->getCreationTime());
	return (0);
}

int	Server::pass( Client &client, const std::vector<std::string> &parameters )
{
	if ( client.getClientState() == REGISTERED )
		return (client.reply(ERR_ALREADYREGISTERED(client.getNickName()) + "\r\n" ), 0);
	if ( parameters.empty() )
		return (client.reply(ERR_NEEDMOREPARAMS(client.getNickName(), "PASS") + "\r\n"), 0);
	if ( parameters.at(0) != this->_password )
	{
		client.reply(ERR_PASSWDMISMATCH(client.getNickName()) + "\r\n");
		this->removeClient(client.getClientFD());
		return (-1);
	}
	client.setClientState(AUTHENTICATED);
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

std::vector<std::string>	Server::parseJoinParameters( const std::string &parameterStr )
{
	std::vector<std::string>	parameters;
	std::stringstream			parameterStream(parameterStr);
	std::string					parameter;

	while (std::getline(parameterStream, parameter, ','))
		parameters.push_back(parameter);
	return (parameters);
}

int	Server::join( Client &client, const std::vector<std::string> &parameters )
{
	std::vector<std::string>	channelNames;
	std::vector<std::string>	keys;

	if (client.getClientState() != REGISTERED)
		client.reply(ERR_NOTREGISTERED(client.getNickName()) + "\r\n");
	if (parameters.empty() || parameters.size() > 2)
		return (client.reply(ERR_NEEDMOREPARAMS(client.getNickName(), "JOIN")+ "\r\n"), 0);
	channelNames = parseJoinParameters(parameters.at(0));
	if (parameters.size() == 2)
		keys = parseJoinParameters(parameters.at(1));
	for (size_t i = 0; i < channelNames.size(); ++i)
	{
		std::string	channelName = channelNames[i];
		std::string	channelKey = (i < keys.size()) ? keys[i] : "";
		if (channelName.at(0) != '#')
		{
			client.reply(ERR_BADCHANMASK(channelName) + "\r\n");
			continue ;
		}
		Channel* channel = NULL;
		std::map<std::string, Channel*>::iterator it = this->_channels.find(channelName);
		bool	newChannel = (it == this->_channels.end());
		if (!newChannel)
		{
			channel = it->second;
			if (channel->checkChannelModes(client, channelName, channelKey) < 0)
				continue ;
		}
		else
			channel = new Channel(channelName);
		channel->addClient(&client);
		if (newChannel)
		{
			channel->addOperator(&client);
			this->_channels[channelName] = channel;
		}
		channel->removeInvite(&client);
		channel->broadcasting(RPL_JOIN(client.getPrefix(), channelName) + "\r\n");
		if (!channel->getTopic().empty())
			client.reply(RPL_TOPIC(client.getNickName(), channelName, channel->getTopic()) + "\r\n");
		client.reply(RPL_NAMREPLY(client.getNickName(), channelName, channel->getNameList()) + "\r\n");
		client.reply(RPL_ENDOFNAMES(client.getNickName(), channelName));
	}
	return (0);
}



