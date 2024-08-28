/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kqueue.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 07:41:16 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/28 15:15:24 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Kqueue.hpp"

Kqueue::Kqueue()
{
	this->_kq = kqueue();
	if (this->_kq < 0)
		throw (std::runtime_error("Error: Failed to create kqueue. Please try again!"));
	_events.resize(MAX_EVENTS);
}

Kqueue::~Kqueue()
{
	close(this->_kq);
}

void	Kqueue::add(int fd, uint32_t flags)
{
	struct kevent	ev;

	EV_SET(&ev, fd, EVFILT_READ, flags, 0, 0, NULL);
	if (kevent(this->_kq, &ev, 1, NULL, 0, NULL) < 0)
		throw (std::runtime_error("Error: Failed to add file descriptor to kqueue. Please try again!"));
}

void	Kqueue::remove(int fd)
{
	struct kevent	ev;

	EV_SET(&ev, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
	if (kevent(this->_kq, &ev, 1, NULL, 0, NULL) < 0)
		throw (std::runtime_error("Error: Failed to remove file descriptor from kqueue. Please try again!"));
}

std::vector<struct kevent>	Kqueue::wait()
{
	int nfds = kevent(this->_kq, NULL, 0, _events.data(), MAX_EVENTS, NULL);
	if (nfds < 0)
		throw (std::runtime_error("Error: Failed to wait on kqueue. Please try again!"));
	return (std::vector<struct kevent>(_events.begin(), _events.begin() + nfds));
}