/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:08:21 by ael-khel          #+#    #+#             */
/*   Updated: 2024/08/30 22:47:45 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define ERR_NEEDMOREPARAMS(nickName, command)                       ":ft_irc 461 " + nickName + " " + command + " :Not enough parameters" + "\r\n"
#define ERR_ALREADYREGISTERED(nickName)                             ":ft_irc 462 " + nickName + " :You may not register" + "\r\n"
#define ERR_PASSWDMISMATCH(nickName)                                ":ft_irc 464 " + nickName + " :Password is incorrect" + "\r\n"
#define ERR_NOTREGISTERED(nickName)                                 ":ft_irc 451 " + nickName + " :You have not registered" + "\r\n"
#define ERR_UNKNOWNCOMMAND(nickName, command)                       ":ft_irc 421 " + nickName + " " + command + " :Unknown command"  + "\r\n"
#define ERR_NONICKNAMEGIVEN(nickName)                               ":ft_irc 431 " + nickName + " :No nickname given" + "\r\n"
#define ERR_ERRONEUSNICKNAME(nickName, nick)                        ":ft_irc 432 " + nickName + " " + nick + " :Erroneus nickname" + "\r\n"
#define ERR_NICKNAMEINUSE(nickName, nick)                           ":ft_irc 433 " + nickName + " " + nick + " :Nickname is already in use" + "\r\n"
#define ERR_NOSUCHCHANNEL(nickName, channel)                        ":ft_irc 403 " + nickName + " " + channel + " :No such channel" + "\r\n"
#define ERR_CHANNELISFULL(nickName, channel)                        ":ft_irc 471 " + nickName + " " + channel + " :Cannot join channel (+l)" + "\r\n"
#define ERR_BADCHANNELKEY(nickName, channel)                        ":ft_irc 475 " + nickName + " " + channel + " :Cannot join channel (+k)" + "\r\n"
#define ERR_BADCHANMASK(channel)                                    ":ft_irc 476 " + channel + " :Bad Channel Mask" + "\r\n"
#define ERR_INVITEONLYCHAN(nickName, channel)                       ":ft_irc 473 " + nickName + " " + channel + " :Cannot join channel (+i)" + "\r\n"
#define ERR_NOSUCHNICK(nickName, nick)                              ":ft_irc 401 " + nickName + " " + nick + " :No such nick" + "\r\n"

#define ERR_NOTONCHANNEL(nickName, channel)                         ":ft_irc 442 " + nickName + " " + channel + " :You're not on that channel" + "\r\n"
#define ERR_CHANOPRIVSNEEDED(nickName, channel)                     ":ft_irc 482 " + nickName + " " + channel + " :You're not channel operator" + "\r\n"

#define ERR_USERONCHANNEL(nickName, nick, channel)                  ":ft_irc 443 " + nickName + " " + nick + " " + channel + " :is already on channel" + "\r\n"
#define ERR_USERNOTINCHANNEL(nickName, nick, channel)               ":ft_irc 441 " + nickName + " " + nick + " " + channel + " :They aren't on that channel" + "\r\n"

#define ERR_UNKNOWNMODE(nickName, mode)                             ":ft_irc 472 " + nickName + " " + mode + " :is unknown mode char to me" + "\r\n"

#define ERR_NOTEXTTOSEND(nickName)                                  ":ft_irc 412 " + nickName + " :No text to send" + "\r\n"

#define RPL_NICK(prefix, nickName)                                  prefix + " NICK " + nickName + "\r\n"
#define RPL_JOIN(prefix, channel)                                   prefix + " JOIN " + channel + "\r\n"
#define RPL_INVITE(prefix, nickName, channel)                       prefix + " INVITE " + nickName + " " + channel + "\r\n"
#define RPL_MODE(prefix, channel, modes, modeArgs)                  prefix + " MODE " + channel + " " + modes + modeArgs + "\r\n"
#define RPL_TOPIC_2(prefix, channel, topic)                         prefix + " TOPIC " + channel + " :" + topic + "\r\n"
#define RPL_KICK(prefix, channel, user, reason)                     prefix + " KICK " + channel + " " + user + " :" + reason + "\r\n"
#define RPL_PRIVMSG(prefix, target, msg)                            prefix + " PRIVMSG " + target + " :" + msg + "\r\n"

#define RPL_WELCOME(nickName, prefix)                               ":ft_irc 001 " + nickName + " :Welcome to the Internet Relay Network " + prefix + "\r\n"
#define RPL_YOURHOST(nickName)                                      ":ft_irc 002 " + nickName + " :Your host is ft_irc, running version IRCv3" + "\r\n"
#define RPL_CREATED(nickName, creationTime)                         ":ft_irc 003 " + nickName + " :This server was created " + creationTime + "\r\n"

#define RPL_INVITING(nickName, nick, channel)                       ":ft_irc 341 " + nickName + " " + nick + " " + channel + "\r\n"
#define RPL_TOPIC(nickName, channel, topic)                         ":ft_irc 332 " + nickName + " " + channel + " :" + topic + "\r\n"
#define RPL_NOTOPIC(nickName, channel)                              ":ft_irc 331 " + nickName + " " + channel + " :No topic is set" + "\r\n"
#define RPL_NAMREPLY(nickName, channel, clients)                    ":ft_irc 353 " + nickName + " = " + channel + " :" + clients + "\r\n"
#define RPL_ENDOFNAMES(nickName, channel)                           ":ft_irc 366 " + nickName + " " + channel + " :End of /NAMES list" + "\r\n"
#define RPL_CHANNELMODEIS(nickName, channel, modestring, modeArgs)  ":ft_irc 324 " + nickName + " " + channel + " " + modes + " " + modeArgs + "\r\n"
