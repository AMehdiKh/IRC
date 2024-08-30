/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:10:54 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/30 23:24:00 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

std::vector<std::string>	Server::parseJoinParameters( const std::string &parameterStr )
{
	std::vector<std::string>	parameters;
	std::stringstream			parameterStream(parameterStr);
	std::string					parameter;

	while (std::getline(parameterStream, parameter, ','))
		parameters.push_back(parameter);
	return (parameters);
}

int	Server::join( Client &client, const std::vector<std::string> &parameters )
{
	std::vector<std::string>	channelNames;
	std::vector<std::string>	keys;

	if (client.getClientState() != REGISTERED)
		return(client.reply(ERR_NOTREGISTERED(client.getNickName())), 0);
	if (parameters.empty() || parameters.size() > 2)
		return (client.reply(ERR_NEEDMOREPARAMS(client.getNickName(), "JOIN")), 0);
	channelNames = parseJoinParameters(parameters.at(0));
	if (parameters.size() == 2)
		keys = parseJoinParameters(parameters.at(1));
	for (size_t i = 0; i < channelNames.size(); ++i)
	{
		std::string	channelName = channelNames[i];
		std::string	channelKey = (i < keys.size()) ? keys[i] : "";
		if (channelName.at(0) != '#')
		{
			client.reply(ERR_BADCHANMASK(channelName));
			continue ;
		}
		Channel* channel = NULL;
		std::map<std::string, Channel*>::iterator it = this->_channels.find(channelName);
		bool	newChannel = (it == this->_channels.end());
		if (!newChannel)
		{
			channel = it->second;
			if (channel->checkChannelModes(client, channelName, channelKey) < 0)
				continue ;
		}
		else
			channel = new Channel(channelName);
		channel->addClient(&client);
		if (newChannel)
		{
			channel->addOperator(&client);
			this->_channels[channelName] = channel;
		}
		channel->removeInvite(&client);
		channel->broadcasting(RPL_JOIN(client.getPrefix(), channelName), NULL);
		if (!channel->getTopic().empty())
			client.reply(RPL_TOPIC(client.getNickName(), channelName, channel->getTopic()));
		else
			client.reply(RPL_NOTOPIC(client.getNickName(), channelName));
		client.reply(RPL_NAMREPLY(client.getNickName(), channelName, channel->getNameList()));
		client.reply(RPL_ENDOFNAMES(client.getNickName(), channelName));
	}
	return (0);
}