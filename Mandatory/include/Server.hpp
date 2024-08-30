/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:19:38 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/30 22:41:08 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Kqueue.hpp"
#include "Client.hpp"
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include "Response.hpp"
#include "Channel.hpp"
#include <fcntl.h>


#define SERVER_NAME "ft_irc"

typedef std::map< int, Client * > ClientsMap;
typedef std::map< std::string, Channel* > ChannelsMap;


class	Server {

	private	:

		Kqueue		_kqueue;
		int			_port;
		std::string	_password;
		time_t		_creationTime;
		int			_server_fd;
		ClientsMap	_clients;
		ChannelsMap	_channels;

	public	:

		Server( int, std::string );
		~Server( );

		void	initServer( void );
		void	run( void );
		void	acceptConnection( void );
		void	removeClient( int );
		void	setNonBlocking( int );

		const std::string	getCreationTime( void ) const;
		
		void	handleClient( Client & );
		int		handleCommands(Client &, const Messages::iterator & );


		int	checkNickNameForm( const std::string & );
		int	checkNickNameInUse( const std::string & );

		std::vector<std::string>	parseJoinParameters( const std::string & );
		
		Client*						findClientByNickname( const std::string );
		Channel*					findChannel( const std::string );

		int	pass( Client &, const std::vector<std::string> & );
		int	nick( Client &, const std::vector<std::string> & );
		int	user( Client &, const std::vector<std::string> & );
		int	join( Client &, const std::vector<std::string> & );
		int	invite( Client &, const std::vector<std::string> & );
		int	mode( Client &, const std::vector<std::string> & );
		int	topic( Client &, const std::vector<std::string> & );
		int	kick( Client &, const std::vector<std::string> & );
		int	privmsg( Client &, const std::vector<std::string> & );
};