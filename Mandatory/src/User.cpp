/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:09:54 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/28 19:00:57 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp

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