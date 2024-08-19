/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:50:21 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/19 07:43:13 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"
#include <sstream>
#include <vector>



Client::Client( int client_fd, std::string ip ) : _client_fd(client_fd), _ip(ip), _clientState(UNREGISTERED)
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

const std::string&	Client::getFullName( void ) const
{
	return (this->_fullName);
}

const ClientState&	Client::getClientState( void ) const
{
	return (this->_clientState);
}

const Messages&		Client::getMessages( void ) const
{
	return (this->_messages);
}


void				Client::setNickName( const std::string nickName )
{
	this->_nickName = nickName;
}

void				Client::setUserName( const std::string userName )
{
	this->_userName = userName;
}

void				Client::setFullName( const std::string fullName )
{
	this->_fullName = fullName;
}

void				Client::setClientState( const ClientState clientState )
{
	this->_clientState = clientState;
}

void	Client::parseMessages( const std::string &data )
{
	std::stringstream	messageStream(data);
	std::string			line;
	std::string			word;
	std::string			firstWord;

	while (std::getline(messageStream, line))
	{
		if (!line.empty() && line.at(line.size() - 1) == '\r')
			line.pop_back();

		std::vector<std::string>	parameters;
		std::stringstream			lineStream(line);

		std::getline(lineStream >> std::ws, firstWord, ' ');
		this->_messages[firstWord] = parameters;
		while (std::getline(lineStream, word, ' '))
		{
			if (word.at(0) == ':')
			{
				std::string	tmp = word.erase(0,1);
				std::getline(lineStream, word, '\0');
				word = tmp + " " + word;
				this->_messages[firstWord].push_back(word);
				break ;
			}
			else
				this->_messages[firstWord].push_back(word);
		}
	}
}
