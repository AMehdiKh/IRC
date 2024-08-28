/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:19:38 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/28 08:55:50 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <bits/types/time_t.h>
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
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include "Response.hpp"
#include "Channel.hpp"


#define SERVER_NAME "ft_irc"

typedef std::map< int, Client * > ClientsMap;
typedef std::map< std::string, Channel* > ChannelsMap;


class	Server {

	private	:

		Epoll						_epoll;
		int							_port;
		std::string					_password;
		time_t						_creationTime;
		int							_server_fd;
		ClientsMap					_clients;
		ChannelsMap					_channels;

	public	:

		Server( int port, std::string password );
		~Server( );

		void	initServer( void );
		void	run( void );
		void	acceptConnection( void );
		void	removeClient( int );

		const std::string	getCreationTime( void ) const;

		
		void	handleClient( Client & );
		int		handleCommands(Client &client, const Messages::iterator & );


		int	checkNickNameForm( const std::string & );
		int	checkNickNameInUse( const std::string &nickName );

		std::vector<std::string>	parseJoinParameters( const std::string & );

		int	pass( Client &, const std::vector<std::string> & );
		int	nick( Client &, const std::vector<std::string> & );
		int	user( Client &, const std::vector<std::string> & );
		int	join( Client &, const std::vector<std::string> & );

};