/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:52:14 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/30 00:42:08 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int	Server::invite( Client &client, const std::vector<std::string> &parameters )
{
	if (client.getClientState() != REGISTERED)
		return(client.reply(ERR_NOTREGISTERED(client.getNickName())), 0);
	if (parameters.size() != 2 || parameters.at(0).empty() || parameters.at(1).empty())
		return (client.reply(ERR_NEEDMOREPARAMS(client.getNickName(), "INVITE")), 0);
	std::string	nickName(parameters.at(0));
	std::string	channelName(parameters.at(1));
	Client		*invitedClient = this->findClientByNickname(nickName);
	if (!invitedClient)
		return (client.reply(ERR_NOSUCHNICK(client.getNickName(), nickName)), 0);
	Channel		*channel = this->findChannel(channelName);
	if (!channel)
		return (client.reply(ERR_NOSUCHCHANNEL(client.getNickName(), channelName)), 0);
	if (!channel->isClientJoined(&client))
		return (client.reply(ERR_NOTONCHANNEL(client.getNickName(), channelName)), 0);
	if (channel->getInviteOnly() && !channel->isClientOperator(&client))
		return (client.reply(ERR_CHANOPRIVSNEEDED(client.getNickName(), channelName)), 0);
	if (channel->isClientJoined(invitedClient))
		return(client.reply(ERR_USERONCHANNEL(client.getNickName(), nickName, channelName)), 0);
	channel->inviteClient(invitedClient);
	client.reply(RPL_INVITING(client.getNickName(), nickName, channelName));
	invitedClient->reply(RPL_INVITE(client.getPrefix(), nickName, channelName));
	return (0);
}