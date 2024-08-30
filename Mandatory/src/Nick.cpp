/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:08:25 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/31 00:08:59 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int	Server::nick( Client &client, const std::vector<std::string> &parameters )
{
	if (client.getClientState() == UNREGISTERED)
		return (0);
	if (parameters.empty() || parameters.at(0).empty())
		return (client.reply(ERR_NONICKNAMEGIVEN(client.getNickName())), 0);
	if (this->checkNickNameForm(parameters.at(0)) < 0)
		return (client.reply(ERR_ERRONEUSNICKNAME(client.getNickName(), parameters.at(0))), 0);
	if (client.getNickName() == parameters.at(0))
		return (0);
	if (this->checkNickNameInUse(parameters.at(0)) < 0)
		return (client.reply(ERR_NICKNAMEINUSE(client.getNickName(), parameters.at(0))), 0);
	if (client.getClientState() == REGISTERED)
		client.reply(RPL_NICK(client.getPrefix(), parameters.at(0)));
	client.setNickName(parameters.at(0));
	if (client.getClientState() != REGISTERED)
		client.welcome(this->getCreationTime());
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