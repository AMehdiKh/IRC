/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:50:09 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/15 07:42:36 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <unistd.h>

class	Client {

	private	:

		int			_client_fd;
		std::string	_ip;

	public	:

		Client( int, std::string );
		~Client( );

		const int&			getClientFD( void ) const;
		const std::string&	getIP( void ) const;

};