/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:08:21 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/25 07:48:36 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define ERR_ALREADYREGISTERED(nickName)                   ":ft_irc 462 " + nickName + " :You may not register"
#define ERR_PASSWDMISMATCH(nickName)                      ":ft_irc 464 " + nickName + " :Password is incorrect"
#define ERR_NEEDMOREPARAMS(nickName, command)             ":ft_irc 464 " + nickName + " " + command + " :Not enough parameters"
#define ERR_NOTREGISTERED(nickName)                       ":ft_irc 451 " + nickName + " :You have not registered"
#define ERR_UNKNOWNCOMMAND(nickName, command)             ":ft_irc 421 " + nickName + " " + command + " :Unknown command" 
#define ERR_NONICKNAMEGIVEN(nickName)                     ":ft_irc 431 " + nickName + " :No nickname given"
#define ERR_ERRONEUSNICKNAME(nickName, nick)              ":ft_irc 432 " + nickName + " " + nick + " :Erroneus nickname"
#define ERR_NICKNAMEINUSE(nickName, nick)                 ":ft_irc 433 " + nickName + " " + nick + " :Nickname is already in use"

#define RPL_WELCOME(nickName, prefix)				      ":ft_irc 001 " + nickName + " :Welcome to the Internet Relay Network " + prefix
#define RPL_YOURHOST(nickName)                            ":ft_irc 002 " + nickName + " :Your host is ft_irc, running version IRCv3"
#define RPL_CREATED(nickName, creationTime)              ":ft_irc 003 " + nickName + " :This server was created " + creationTime

#define RPL_NICK(prefix, nickName)                        prefix + " NICK " + nickName