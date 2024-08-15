/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Epoll.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 07:41:16 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/15 07:43:53 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Epoll.hpp"

Epoll::Epoll( void )
{
	this->_epoll_fd = epoll_create1( 0 );
	if (this->_epoll_fd < 0)
		throw std::runtime_error("Error: Failed to create epoll file descriptor. Please try again!");
	this->_events.resize( MAX_EVENTS );
}

Epoll::~Epoll( )
{
	close( this->_epoll_fd );
}

void	Epoll::add( int fd, uint32_t events )
{
	struct epoll_event	event;

	event.data.fd = fd;
	event.events = events;
	if (epoll_ctl(this->_epoll_fd, EPOLL_CTL_ADD, fd, &event) < 0)
		throw std::runtime_error("Error: Failed to add file descriptor to epoll. Please try again!");
}

void	Epoll::modify( int fd, uint32_t events )
{
	struct epoll_event event;

	event.data.fd = fd;
	event.events = events;
	if (epoll_ctl(this->_epoll_fd, EPOLL_CTL_MOD, fd, &event) < 0)
		throw std::runtime_error("Error: Failed to modify file descriptor in epoll. Please try again!");

}

void	Epoll::remove( int fd )
{
	if (epoll_ctl(this->_epoll_fd, EPOLL_CTL_DEL, fd, NULL) < 0 )
		throw std::runtime_error("Error: Failed to remove file descriptor from epoll. Please try again!");
}

std::vector<struct epoll_event>	Epoll::wait( void )
{
	int nfds = epoll_wait(this->_epoll_fd, this->_events.data(), MAX_EVENTS, -1);
	if (nfds < 0)
		throw std::runtime_error("Error: Failed to wait on epoll file descriptor. Please try again!");
	return ( std::vector<struct epoll_event>(this->_events.begin(), this->_events.begin() + nfds) );
}
