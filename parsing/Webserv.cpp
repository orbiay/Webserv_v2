/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomman <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:55:14 by aomman            #+#    #+#             */
/*   Updated: 2023/03/11 18:21:11 by aomman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Webserv.hpp"

Server::Server(){}

void	Server::set_server(std::ifstream &file)
{
	std::string	line;

	while (!file.eof())
	{
		getline(file, line);
		if (line == "server:")
			this->server = line;
	}
}

std::string	Server::get_server(void) const
{
	return (this->server);
}

Server::~Server(){}