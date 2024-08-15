/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Epoll.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 01:47:20 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/15 07:39:24 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/epoll.h>
#include <vector>
#include <stdexcept>
#include <unistd.h>

#define MAX_EVENTS 20

class Epoll	{

	private :

		int								_epoll_fd;
		std::vector<struct epoll_event>	_events;

	public	:

		Epoll( void );
		~Epoll( );

		void							add( int fd, uint32_t events );
		void							modify( int fd, uint32_t events );
		void							remove( int fd );
		std::vector<struct epoll_event>	wait( void );

};
