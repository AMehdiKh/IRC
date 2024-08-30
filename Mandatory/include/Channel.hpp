/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:05:05 by codespace         #+#    #+#             */
/*   Updated: 2024/08/30 23:24:40 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include <algorithm>

class	Channel	{

	private	:
		std::string				_name;
		std::string				_topic;
		std::string 			_key;
		std::vector<Client*>	_clients;
		std::vector<Client*>	_operators;
		std::vector<Client*>	_invitedClients;
		size_t					_userLimit;
		bool					_inviteOnly;
		bool					_topicRestricted;

	public	:
		Channel( const std::string );
		~Channel( );
		
		const std::string&			getName( void ) const;
		const std::string&			getTopic( void ) const;
		const std::string&			getKey( void ) const;
		const size_t&				getUserLimit( void ) const;
		bool						getInviteOnly( void ) const;
		bool						getTopicRestricted( void ) const;
		std::vector<Client*>&		getClients( void );
		std::vector<Client*>&		getOperators( void );
		size_t						getChannelSize( void ) const;



		void						setTopic( const std::string );
		void						setKey( const std::string );
		void						setUserLimit( const size_t );
		void						setInviteOnly( const bool );
		void						setTopicRestricted( const bool );

		bool						isClientJoined( Client* ) const;
		void						addClient( Client* );
		void						removeClient( Client* );
		
		bool						isClientOperator( Client* ) const;
		void						addOperator( Client* );
		void						removeOperator( Client* );

		bool						isClientInvited( Client* ) const;
		void						inviteClient( Client* );
		void						removeInvite( Client* );

		int							checkChannelModes( Client &, const std::string &, const std::string & ) const;
		const std::string			getNameList( void ) const;
		std::string					intToString( int );

		void						sendChannelModes( Client& );
		void						handleOperatorMode( Client *, bool );


		void						broadcasting( const std::string, Client * );
};