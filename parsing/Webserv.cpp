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

Pserver::Pserver(){}

void	Pserver::set_server(std::ifstream &file)
{
	std::string	line;

	while (!file.eof())
	{
		getline(file, line);
		if (line == "server:")
			this->server = line;
	}
}

std::string	Pserver::get_server(void) const
{
	return (this->server);
}

Pserver::~Pserver(){}