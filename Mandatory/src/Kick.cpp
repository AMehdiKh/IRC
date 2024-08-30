/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:03:48 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/30 09:54:01 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int	Server::kick( Client &client, const std::vector<std::string> &parameters )
{
	std::string	targetNickname;
	std::string	reason = "Kicked from channel";

	if (client.getClientState() != REGISTERED)
		return(client.reply(ERR_NOTREGISTERED(client.getNickName())), 0);
	if (parameters.empty() || parameters.size() < 2)
		return (client.reply(ERR_NEEDMOREPARAMS(client.getNickName(), "KICK")), 0);
	targetNickname = parameters.at(1);
	if (parameters.size() > 2)
		reason = parameters.at(2);
	Channel	*channel = this->findChannel(parameters.at(0));
	if (!channel)
		return (client.reply(ERR_NOSUCHCHANNEL(client.getNickName(), channel->getName())), 0);
	if (!channel->isClientJoined(&client))
		return (client.reply(ERR_NOTONCHANNEL(client.getNickName(), channel->getName())), 0);
	if (!channel->isClientOperator(&client))
		return (client.reply(ERR_CHANOPRIVSNEEDED(client.getNickName(), channel->getName())), 0);
	if (!channel->isClientJoined(this->findClientByNickname(targetNickname)))
		return (client.reply(ERR_USERNOTINCHANNEL(client.getNickName(), targetNickname, channel->getName())), 0);
	channel->removeClient(this->findClientByNickname(targetNickname));
	this->findClientByNickname(targetNickname)->reply(RPL_KICK(client.getPrefix(), channel->getName(), targetNickname, reason));
	channel->broadcasting(RPL_KICK(client.getPrefix(), channel->getName(), targetNickname, reason));
	return (0);
}
		
	