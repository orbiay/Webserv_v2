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

Pserver::Pserver()
{
	this->end = 0;
	this->nloc = 0;
	this->lend = 0;
	this->host = "";
	this->port = 0;
}

const char *Pserver::SyntaxError::what() const throw()
{
	return ("syntax error");
}

void	Pserver::set_end(std::ifstream &f2)
{
	std::string	line;

	while (!f2.eof())
	{
		getline(f2, line);
		if (line == "end")
			this->end++;
	}
}

void	Pserver::set_nLocation(std::ifstream &f)
{
	std::string	line;

	while (!f.eof())
	{
		getline(f, line);
		{
			if (line == "\tlend")
				this->lend++;
			if (line == "end")
				return ;
			if (line.compare(0, 9, "\tlocation") == 0)
				this->nloc++;
		}
	}
}

void	Pserver::set_host(std::ifstream &rf)
{
	std::string line;
	size_t	i;

	while (!rf.eof())
	{
		getline(rf, line);
		if (line.compare(0, 7, "\tlisten") == 0)
		{
			i = line.find(":");
			if (i == std::string::npos)
				throw(SyntaxError());
			this->host = line.substr(8, i - 8);
			this->ports = line.substr(i + 1, line.length() - i);
			this->port = std::atoi(this->ports.c_str());
			return ;
		}
	}
}

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

std::string	Pserver::get_host(void) const
{
	return (this->host);
}

int	Pserver::get_port(void) const
{
	return (this->port);
}

int	Pserver::get_nserv(void) const
{
	return (this->nserv);
}

Pserver::~Pserver(){}