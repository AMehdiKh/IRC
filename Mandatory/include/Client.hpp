/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:50:09 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/28 08:59:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cerrno>
#include "Response.hpp"

#define BUFFER_SIZE 513

typedef std::vector< std::pair< std::string, std::vector<std::string> > > Messages;
typedef std::pair< std::string, std::vector<std::string> > Pair;

enum ClientState { UNREGISTERED, AUTHENTICATED, REGISTERED };

class	Client {

	private	:

		int			_client_fd;
		std::string	_ip;
		std::string	_nickName;
		std::string	_userName;
		std::string	_realName;
		ClientState	_clientState;

	public	:

		Client( int, std::string );
		~Client( );

		const int&			getClientFD( void ) const;
		const std::string&	getIP( void ) const;

		const std::string&	getNickName( void ) const;
		const std::string&	getUserName( void ) const;
		const std::string&	getrealName( void ) const;
		const ClientState&	getClientState( void ) const;
		const Messages&		getMessages( void ) const;
		const std::string	getPrefix( void ) const;
	
		void				setNickName( const std::string );
		void				setUserName( const std::string );
		void				setrealName( const std::string );
		void				setClientState( const ClientState );

		const Messages		parseMessages( const std::string & );
		const std::string	receive( void );
		void				reply( const std::string );
		void				welcome( const std::string );



};