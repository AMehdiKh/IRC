/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 01:58:23 by codespace         #+#    #+#             */
/*   Updated: 2024/08/28 16:25:35 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"
#include <cstddef>
#include <string>

Channel::Channel( const std::string channelName ) : _name(channelName), _userLimit(0), _inviteOnly(false)
{

}

Channel::~Channel( )
{
	
}

void	Channel::broadcasting( const std::string msg )
{
	for (std::vector<Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
		(*it)->reply(msg);
}

const std::string&	Channel::getName( void ) const
{
	return (this->_name);
}

const std::string&	Channel::getTopic( void ) const
{
	return (this->_topic);
}

const std::string&	Channel::getKey( void ) const
{
	return (this->_key);
}

const size_t&	Channel::getUserLimit( void ) const
{
	return (this->_userLimit);
}

bool	Channel::getInviteOnly( void ) const
{
	return (this->_inviteOnly);
}

std::vector<Client*>&	Channel::getClients( void )
{
	return (this->_clients);
}

std::vector<Client*>&	Channel::getOperators( void )
{
	return (this->_operators);
}

size_t	Channel::getChannelSize( void ) const
{
	return (this->_clients.size());
}

void	Channel::setTopic( const std::string topic )
{
	this->_topic = topic;
}

void	Channel::setKey( const std::string key )
{
	this->_key = key;
}

void	Channel::setUserLimit( const size_t userLimit )
{
	this->_userLimit = userLimit;
}

void	Channel::setInviteOnly( const bool inviteOnly )
{
	this->_inviteOnly = inviteOnly;
}

bool	Channel::isClientInvited( Client* client ) const
{
	return (std::find(this->_invitedClients.begin(), this->_invitedClients.end(), client) != this->_invitedClients.end());
}

void	Channel::inviteClient( Client* client )
{
	if (!isClientInvited(client)) 
		this->_invitedClients.push_back(client);
}

void	Channel::removeInvite( Client* client )
{
	this->_invitedClients.erase(std::remove(this->_invitedClients.begin(), this->_invitedClients.end(), client), this->_invitedClients.end());
}

bool	Channel::isClientJoined( Client* client ) const
{
	return (std::find(this->_clients.begin(), this->_clients.end(), client) != this->_clients.end());
}

void	Channel::addClient( Client* client )
{
	if (!isClientJoined(client))
		this->_clients.push_back(client);
}

void	Channel::removeClient( Client* client )
{
	this->_clients.erase(std::remove(this->_clients.begin(), this->_clients.end(), client), this->_clients.end());
}

bool	Channel::isClientOperator( Client* client ) const
{
	return (std::find(this->_operators.begin(), this->_operators.end(), client) != this->_operators.end());
}

void	Channel::addOperator( Client* client )
{
	if (!isClientJoined(client))
		this->_operators.push_back(client);
}

void	Channel::removeOperator( Client* client )
{
	this->_operators.erase(std::remove(this->_operators.begin(), this->_operators.end(), client), this->_operators.end());
}

int	Channel::checkChannelModes(Client &client, const std::string &channelName, const std::string &channelKey) const
{
	if (this->isClientJoined(&client))
		return (-1);
	if (this->getInviteOnly() && !this->isClientInvited(&client))
		return (client.reply(ERR_INVITEONLYCHAN(client.getNickName(), channelName) + "\r\n"), -1);
	if (!this->getKey().empty() && this->getKey() != channelKey)
		return (client.reply(ERR_BADCHANNELKEY(client.getNickName(), channelName) + "\r\n"), -1);
	if (this->getUserLimit() > 0 && this->getChannelSize() >= this->getUserLimit())
		return (client.reply(ERR_CHANNELISFULL(client.getNickName(), channelName) + "\r\n"), -1);
	return (0);
}

const std::string	Channel::getNameList( void ) const
{
	std::string namesList;

	for (size_t i = 0; i < this->getChannelSize(); ++i)
	{
		if (i > 0)
			namesList += " ";
		if (this->isClientOperator(this->_clients.at(i)))
			namesList += "@";
		namesList += this->_clients.at(i)->getNickName();
	}
	std::cout << 
	return (namesList);
}