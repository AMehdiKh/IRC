/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:50:09 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/19 09:24:04 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <unistd.h>

typedef std::map<std::string, std::vector<std::string>> Messages;

enum ClientState { UNREGISTERED, AUTHENTICATED, REGISTERED };

class	Client {

	private	:

		int													_client_fd;
		std::string											_ip;
		std::string											_nickName;
		std::string											_userName;
		std::string											_fullName;
		ClientState											_clientState;
		Messages										 	_messages;

	public	:

		Client( int, std::string );
		~Client( );

		const int&			getClientFD( void ) const;
		const std::string&	getIP( void ) const;

		const std::string&	getNickName( void ) const;
		const std::string&	getUserName( void ) const;
		const std::string&	getFullName( void ) const;
		const ClientState&	getClientState( void ) const;
		const Messages&		getMessages( void ) const;

		void				setNickName( const std::string );
		void				setUserName( const std::string );
		void				setFullName( const std::string );
		void				setClientState( const ClientState );

		void				parseMessages( const std::string & );


};