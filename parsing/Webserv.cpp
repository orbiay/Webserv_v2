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

void	Pserver::set_nserv(std::ifstream &rf)
{
	std::string	line;
	size_t		i;

	while (!rf.eof())
	{
		getline(rf, line);
		if (line.compare(0, 6, "nserv:") == 0)
		{
			i = line.find(" ");
			line = line.substr(i + 1, line.length());
			this->nserv = std::atoi(line.c_str());
			return ;
		}
	}
}

int	Pserver::get_nserv(void) const
{
	return (this->nserv);
}

Pserver::~Pserver(){}