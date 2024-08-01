/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:28:05 by ael-khel          #+#    #+#             */
/*   Updated: 2024/07/27 23:27:36 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <exception>
#include <iostream>

void	handleArguments( int argc, char **argv )
{
	int			port;
	std::string	password;

	// check if user entered two arguments
	if ( argc != 3 )
		throw ( std::invalid_argument("Error: it must be run as follows:\n\t./ircserv <port> <password>\n") );
	// check if port have only numbers
	if ( std::string(argv[1]).find_first_not_of("0123456789") != std::string::npos )
		throw ( std::invalid_argument("Error: the port must contains only numbers.\n") );
	// check if port string size not exceed 5 digits (for the overflow)
	if ( std::string(argv[1]).size() > 5 )
		throw ( std::invalid_argument("Error: invalid port number.\n") );
	// convert port from char * ro int
	port = strtol(argv[1], NULL, 10);
	// check if port have valid range
	if ( port < 1 || port > 65535 )
		throw ( std::invalid_argument("Error: port range not valid.\n") );
	password = argv[2];
}

int	main( int argc, char **argv )
{
	try {
		handleArguments( argc, argv );
	}
	catch ( const std::exception &error ) {
		std::cerr << error.what();
	}

	return (0);
}

