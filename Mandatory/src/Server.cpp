/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:19:48 by ael-khel          #+#    #+#             */
/*   Updated: 2024/07/31 07:01:33 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include <netinet/in.h>
#include <sys/socket.h>

Server::Server( int port, std::string password ) : _port(port), _password(password)
{
	
}
Server::~Server( )
{
	close( this->_server_fd );
}

void	Server::initServer( void )
{
	struct sockaddr_in	addr;
	int					opt = 1;

	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->_port); // convert to network bytes order (big-endian)
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // bind the socket to all available interfaces it will listen for incoming connections on any of the machine's IP addresses

	if ( (this->_server_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) < 0 )
		throw ( std::runtime_error("Error: Unable to create server socket. Please try again.\n") );
	if ( setsockopt(this->_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0 )
		throw ( std::runtime_error("Error: Failed to set socket options. Please try again.\n") );
	if ( bind(this->_server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0 )
		throw ( std::runtime_error("Error: Unable to bind server socket. Please try again.\n") );
	if ( listen(this->_server_fd, 4096) < 0 )
		throw ( std::runtime_error("Error: Failed to listen on server socket. Please try again.\n") );

}