/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:50:21 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/15 07:41:32 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"


Client::Client( int client_fd, std::string ip ) : _client_fd(client_fd), _ip(ip)
{
	
}

Client::~Client( )
{
	close( this->_client_fd );
}

const int&			Client::getClientFD( void ) const
{
	return ( this->_client_fd );
}

const std::string&	Client::getIP( void ) const
{
	return ( this->_ip );
}