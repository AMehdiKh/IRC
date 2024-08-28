/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:52:14 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/28 19:31:38 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int	Server::invite( Client &client, const std::vector<std::string> &parameters )
{
	if (client.getClientState() != REGISTERED)
		return(client.reply(ERR_NOTREGISTERED(client.getNickName()) + "\r\n"), 0);
	if (parameters.size() != 2 || parameters.at(0).empty() || parameters.at(1).empty())
		return (client.reply(461 + "\r\n"), 0);

	std::string	nickName(parameters.at(0));
	std::string	channelName(parameter.at(1));
	Channel		*channel = this->findChannel(channelName);
	if (!channel)
		return (client.reply(403 + "\r\n"), 0);
	if (!channel->isClientOperator(sender))
		return (client.reply(482 + "\r\n"), 0);
	Client		*invitedClient = findClientByNickname(nickName);
	if (!invitedClient)
		return (client.reply(401 + "\r\n"), 0);
	if (channel->isClientInChannel(invitedClient))
		return(client.reply(443 + "\r\n"), 0);
	channel->inviteClient(invitedClient);
	client.reply(341 + "\r\n");
	client.reply(RPL_INVITE(client.getPrefix(), nickName, channel) + "\r\n");

	return (0);
}