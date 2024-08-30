/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:59:44 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/30 23:17:06 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int	Server::privmsg( Client &client, const std::vector<std::string> &parameters )
{
	std::vector<std::string>	targets;
	std::string					msg;

	if (client.getClientState() != REGISTERED)
		return(client.reply(ERR_NOTREGISTERED(client.getNickName())), 0);
	if (parameters.empty() || parameters.size() > 2)
		return (client.reply(ERR_NEEDMOREPARAMS(client.getNickName(), "PRIVMSG")), 0);
	if (parameters.at(1).empty())
		return (client.reply(ERR_NOTEXTTOSEND(client.getNickName())), 0);
	targets = this->parseJoinParameters( parameters.at(0) );
	msg = parameters.at(1);
	for (std::vector<std::string>::iterator it = targets.begin(); it != targets.end(); ++it)
	{
		if (it->at(0) == '#')
		{
			Channel	*channel = this->findChannel(*it);
			if (!channel)
			{
				client.reply(ERR_NOSUCHCHANNEL(client.getNickName(), channel->getName()));
				continue ;
			}
			if (!channel->isClientJoined(&client))
			{
				client.reply(ERR_NOTONCHANNEL(client.getNickName(), channel->getName()));
				continue ;
			}
			channel->broadcasting(RPL_PRIVMSG(client.getPrefix(), channel->getName(), msg), &client);
		}
		else
		{
			Client	*recipient = this->findClientByNickname(*it);
			if (!recipient)
			{
				client.reply(ERR_NOSUCHNICK(client.getNickName(), *it));
				continue ;
			}
			recipient->reply(RPL_PRIVMSG(client.getPrefix(), *it, msg));
		}
	}
	return (0);
}