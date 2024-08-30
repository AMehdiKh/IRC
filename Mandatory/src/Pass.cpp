/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:07:04 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/31 00:08:44 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int	Server::pass( Client &client, const std::vector<std::string> &parameters )
{
	if ( client.getClientState() == REGISTERED )
		return (client.reply(ERR_ALREADYREGISTERED(client.getNickName())), 0);
	if ( parameters.empty() )
		return (client.reply(ERR_NEEDMOREPARAMS(client.getNickName(), "PASS")), 0);
	if ( parameters.at(0) != this->_password )
	{
		client.reply(ERR_PASSWDMISMATCH(client.getNickName()));
		this->removeClient(client.getClientFD());
		return (-1);
	}
	client.setClientState(AUTHENTICATED);
	return (0);
}