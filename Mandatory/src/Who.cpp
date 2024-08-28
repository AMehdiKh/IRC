/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:06:53 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/28 17:08:21 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int	Server::who( Client &client, const std::vector<std::string> &parameters )
{
	if (client.getClientState() != REGISTERED)
		return(client.reply(ERR_NOTREGISTERED(client.getNickName()) + "\r\n"), 0);
	
}
