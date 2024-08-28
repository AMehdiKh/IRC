/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:50:21 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/28 02:00:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"

Client::Client( int client_fd, std::string ip ) :
	_client_fd(client_fd),
	_ip(ip),
	_nickName("*"),
	_userName("*"),
	_realName("*"),
	_clientState(UNREGISTERED)
{
	
}

Client::~Client( )
{
	close( this->_client_fd );
}

const int&			Client::getClientFD( void ) const
{
	return ( this->_client_fd );
}

const std::string&	Client::getIP( void ) const
{
	return ( this->_ip );
}

const std::string&	Client::getNickName( void ) const
{
	return (this->_nickName);
}

const std::string&	Client::getUserName( void ) const
{
	return (this->_userName);
}

const std::string&	Client::getrealName( void ) const
{
	return (this->_realName);
}

const ClientState&	Client::getClientState( void ) const
{
	return (this->_clientState);
}

const std::string	Client::getPrefix( void ) const
{
	return (":" + this->getNickName() + "!" + this->getUserName() + "@" + this->getIP());
}	

void				Client::setNickName( const std::string nickName )
{
	this->_nickName = nickName;
}

void				Client::setUserName( const std::string userName )
{
	this->_userName = userName;
}

void				Client::setrealName( const std::string realName )
{
	this->_realName = realName;
}

void				Client::setClientState( const ClientState clientState )
{
	this->_clientState = clientState;
}

const Messages	Client::parseMessages( const std::string &data )
{
	Messages			messages;
	std::stringstream	messageStream(data);
	std::string			line;
	std::string			word;
	std::string			command;

	while (std::getline(messageStream, line, '\n'))
	{
		if (!line.empty() && line.at(line.size() - 1) == '\r')
			line.erase(line.size() - 1, 1);
		std::vector<std::string>	parameters;
		std::stringstream			lineStream(line);

		std::getline(lineStream >> std::ws, command, ' ');
		messages.push_back(Pair(command, parameters));
		while (std::getline(lineStream, word, ' '))
		{
			if (word.at(0) == ':')
			{
				std::string	tmp = word.erase(0,1);
				if (std::getline(lineStream, word, '\0'))
					word = tmp + " " + word;
				else
					word = tmp;
				messages.back().second.push_back(word);
				break ;
			}
			else
				messages.back().second.push_back(word);
		}
	}
	return (messages);
}

const std::string	Client::receive( void )
{
	char	messageBuffer[BUFFER_SIZE] = { 0 };

	if (recv(this->getClientFD(), messageBuffer, sizeof(messageBuffer), 0) < 0)
		if (errno != EAGAIN && errno != EWOULDBLOCK)
			throw ( std::runtime_error("Error: Failed to receive data. Please try again!\n") );
	if (messageBuffer[BUFFER_SIZE - 1] != '\0') // Truncate the message if is larger than BUFFER_SIZE
	{
		messageBuffer[BUFFER_SIZE - 3] = '\r';
		messageBuffer[BUFFER_SIZE - 2] = '\n';
		messageBuffer[BUFFER_SIZE - 1] = '\0';
	}
	return (messageBuffer);
}

void	Client::reply( const std::string reply )
{
	if (send(this->getClientFD(), reply.c_str(), reply.size(), 0) < 0)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK)
			throw ( std::runtime_error("Error: Failed to send data. Please try again!\n") );
	}
}

void	Client::welcome( const std::string creationTime )
{
	if (this->getUserName() == "*" || this->getrealName() == "*" || this->getNickName() == "*")
		return ;
	this->reply(RPL_WELCOME(this->getNickName(), this->getPrefix()) + "\r\n");
	this->reply(RPL_YOURHOST(this->getNickName()) + "\r\n");
	this->reply(RPL_CREATED(this->getNickName(), creationTime) + "\r\n");
	this->setClientState(REGISTERED);
}
