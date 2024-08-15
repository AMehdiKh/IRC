/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:19:38 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/15 07:43:26 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Epoll.hpp"
#include "Client.hpp"
#include <cerrno>

class	Server {

	private	:

		int							_port;
		std::string					_password;
		int							_server_fd;
		std::map< int, Client * >	_clients;

	public	:

		Server( int port, std::string password );
		~Server( );

		void	initServer( void );
		void	run( void );
		Client*	acceptConnection( void );
		void	removeClient( int );
};