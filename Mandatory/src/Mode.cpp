/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:35:56 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/30 23:24:16 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int	Server::mode( Client &client, const std::vector<std::string> &parameters )
{
	std::string	modes;
	std::string	modeChanges;
	std::string	modeArgs;
	char		mode;
	size_t		argIndex;
	bool		adding;

	if (client.getClientState() != REGISTERED)
		return(client.reply(ERR_NOTREGISTERED(client.getNickName())), 0);
	if (parameters.empty())
		return (client.reply(ERR_NEEDMOREPARAMS(client.getNickName(), "MODE")), 0);
	Channel		*channel = this->findChannel(parameters.at(0));
	if (!channel)
		return (client.reply(ERR_NOSUCHCHANNEL(client.getNickName(), channel->getName())), 0);
	if (!channel->isClientJoined(&client))
		return (client.reply(ERR_NOTONCHANNEL(client.getNickName(), channel->getName())), 0);
	if (parameters.size() == 1)
		return (channel->sendChannelModes(client), 0);
	if (!channel->isClientOperator(&client))
		return (client.reply(ERR_CHANOPRIVSNEEDED(client.getNickName(), channel->getName())), 0);
	modes = parameters.at(1);
	adding = true;
	argIndex = 2;
	for (size_t i = 0; i < modes.size(); ++i)
	{
		mode = modes.at(i);
		if (mode == '+' || mode == '-')
			adding = (mode == '+') ? true : false;
		else if (mode == 'i')
		{
			channel->setInviteOnly(adding);
			modeChanges += (adding ? "+" : "-");
			modeChanges += mode;
		}
		else if (mode == 't')
		{
			channel->setTopicRestricted(adding);
			modeChanges += (adding ? "+" : "-");
			modeChanges += mode;
		}
		else if (mode == 'k')
		{
			if (adding && argIndex < parameters.size())
			{
				channel->setKey(parameters.at(argIndex));
				modeChanges += "+";
				modeChanges += mode;
				modeArgs += " " + parameters.at(argIndex);
				++argIndex;
			}
			else if (!adding)
			{
				channel->setKey("");
				modeChanges += "-";
				modeChanges += mode;
			}
			else
				client.reply(ERR_NEEDMOREPARAMS(client.getNickName(), "MODE +k"));
		}
		else if (mode == 'o')
		{
			if (argIndex < parameters.size())
			{
				channel->handleOperatorMode(this->findClientByNickname(parameters.at(argIndex)), adding);
				modeChanges += (adding ? "+" : "-");
				modeChanges += mode;
				modeArgs += " " + parameters.at(argIndex);
				++argIndex;
			}
			else
				client.reply(ERR_NEEDMOREPARAMS(client.getNickName(), "MODE " + (adding ? "+" : "-") + "o"));
		}
		else if (mode == 'l')
		{
			if (adding && argIndex < parameters.size())
			{
				int limit = strtol(parameters.at(argIndex).c_str(), NULL, 10);
				if (limit < 0) 
					continue ;
				channel->setUserLimit(limit);
				modeChanges += "+";
				modeChanges += mode;
				modeArgs += " " + parameters.at(argIndex);
				++argIndex;
			}
			else if (!adding)
			{
				channel->setUserLimit(0);
				modeChanges += "-";
				modeChanges += mode;
			}
			else
				client.reply(ERR_NEEDMOREPARAMS(client.getNickName(), "MODE +l"));
		}
		else
			client.reply(ERR_UNKNOWNMODE(client.getNickName(), mode));
	}
	if (!modeChanges.empty())
        channel->broadcasting(RPL_MODE(client.getPrefix(), channel->getName(), modeChanges, modeArgs), NULL);
	return (0);
}

void	Channel::sendChannelModes( Client &client )
{
	std::string modes = "+";
	std::string modeArgs;

	if (this->getInviteOnly())
		modes += "i";
	if (this->getTopicRestricted())
		modes += "t";
	if (!this->getKey().empty())
	{
		modes += "k";
		modeArgs += " " + this->getKey();
	}
	if (this->getUserLimit() > 0)
	{
		modes += "l";
		modeArgs += " " + this->intToString(this->getUserLimit());
	}
	client.reply(RPL_CHANNELMODEIS(client.getNickName(), this->getName(), modes, modeArgs));
}

void	Channel::handleOperatorMode(Client *client, bool adding)
{
	if (client && this->isClientJoined(client))
	{
		if (adding)
			this->addOperator(client);
		else
			this->removeOperator(client);
	}
}