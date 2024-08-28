/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kqueue.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 01:47:20 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/28 15:10:37 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <stdexcept>
#include <unistd.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

#define MAX_EVENTS 20

class Kqueue	{

	private :

		int							_kq;
		std::vector<struct kevent>	_events;

	public	:

		Kqueue( void );
		~Kqueue( );

		void							add( int fd, uint32_t events );
		void							remove( int fd );
		std::vector<struct kevent>		wait( void );

};
