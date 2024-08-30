/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 07:26:51 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/30 09:54:19 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int	Server::topic( Client &client, const std::vector<std::string> &parameters )
{
	if (client.getClientState() != REGISTERED)
		return(client.reply(ERR_NOTREGISTERED(client.getNickName())), 0);
	if (parameters.empty() || parameters.size() > 2)
		return (client.reply(ERR_NEEDMOREPARAMS(client.getNickName(), "TOPIC")), 0);
	Channel	*channel = findChannel(parameters.at(0));
	if (!channel)
		return (client.reply(ERR_NOSUCHCHANNEL(client.getNickName(), channel->getName())), 0);
	if (!channel->isClientJoined(&client))
		return (client.reply(ERR_NOTONCHANNEL(client.getNickName(), channel->getName())), 0);
	if (parameters.size() == 1)
	{
		if (!channel->getTopic().empty())
			return (client.reply(RPL_TOPIC(client.getNickName(), channel->getName(), channel->getTopic())), 0);
		else
			return (client.reply(RPL_NOTOPIC(client.getNickName(), channel->getName())), 0);
	}
	else
	{
		if (!channel->isClientOperator(&client) && channel->getTopicRestricted())
			return (client.reply(ERR_CHANOPRIVSNEEDED(client.getNickName(), channel->getName())), 0);
		channel->setTopic(parameters.at(1));
		channel->broadcasting(RPL_TOPIC_2(client.getPrefix(), channel->getName(), channel->getTopic()));
	}
	return (0);
}