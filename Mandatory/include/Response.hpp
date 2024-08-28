/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:08:21 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/28 19:34:05 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define ERR_NEEDMOREPARAMS(nickName, command)             ":ft_irc 461 " + nickName + " " + command + " :Not enough parameters"
#define ERR_ALREADYREGISTERED(nickName)                   ":ft_irc 462 " + nickName + " :You may not register"
#define ERR_PASSWDMISMATCH(nickName)                      ":ft_irc 464 " + nickName + " :Password is incorrect"
#define ERR_NOTREGISTERED(nickName)                       ":ft_irc 451 " + nickName + " :You have not registered"
#define ERR_UNKNOWNCOMMAND(nickName, command)             ":ft_irc 421 " + nickName + " " + command + " :Unknown command" 
#define ERR_NONICKNAMEGIVEN(nickName)                     ":ft_irc 431 " + nickName + " :No nickname given"
#define ERR_ERRONEUSNICKNAME(nickName, nick)              ":ft_irc 432 " + nickName + " " + nick + " :Erroneus nickname"
#define ERR_NICKNAMEINUSE(nickName, nick)                 ":ft_irc 433 " + nickName + " " + nick + " :Nickname is already in use"
#define ERR_NOSUCHCHANNEL(nickName, channel)              ":ft_irc 403 " + nickName + " " + channel + " :No such channel"
#define ERR_CHANNELISFULL(nickName, channel)              ":ft_irc 471 " + nickName + " " + channel + " :Cannot join channel (+l)"
#define ERR_BADCHANNELKEY(nickName, channel)              ":ft_irc 475 " + nickName + " " + channel + " :Cannot join channel (+k)"
#define ERR_BADCHANMASK(channel)                          ":ft_irc 476 " + channel + " :Bad Channel Mask"
#define ERR_INVITEONLYCHAN(nickName, channel)             ":ft_irc 473 " + nickName + " " + channel + " :Cannot join channel (+i)"

#define RPL_NICK(prefix, nickName)                        prefix + " NICK " + nickName
#define RPL_JOIN(prefix, channel)                         prefix + " JOIN " + channel
#define RPL_INVITE(prefix, nickName, channel)             prefix + " INVITE " + nickName + " " channel

#define RPL_WELCOME(nickName, prefix)                     ":ft_irc 001 " + nickName + " :Welcome to the Internet Relay Network " + prefix
#define RPL_YOURHOST(nickName)                            ":ft_irc 002 " + nickName + " :Your host is ft_irc, running version IRCv3"
#define RPL_CREATED(nickName, creationTime)               ":ft_irc 003 " + nickName + " :This server was created " + creationTime

#define RPL_TOPIC(nickName, channel, topic)               ":ft_irc 332 " + nickName + " " + channel + " :" + topic

#define RPL_NAMREPLY(nickName, channel, clients)          "ft_irc 353 " + nickName + " = " + channel + " :" + clients
#define RPL_ENDOFNAMES(nickName, channel)                 "ft_irc 366 " + nickName + " " + channel + " :End of /NAMES list" 
