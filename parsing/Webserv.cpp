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
	this->cgi = false;
	this->cgi_path = "";
	this->cgi_extention = "";
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
			this->port = std::atoi(line.substr(i + 1, line.length() - i).c_str());
			this->set_method(rf);
			return ;
		}
	}
}

void	Pserver::set_cgi_path(std::ifstream &rf)
{
	std::string	line;
	size_t	i;
	size_t	j;

	while (!rf.eof())
	{
		getline(rf, line);
		if (line.compare(0, 4, "\t\t\t/") == 0)
		{
			i = line.find("/");
			this->cgi_path = line.substr(i, line.length() - 7);
			j = line.find(" ");
			if (j == std::string::npos)
				return ;
			this->cgi_extention = line.substr(j + 1);
			return ;
		}
	}
}

void	Pserver::set_cgi(std::ifstream &rf)
{
	std::string	line;
	size_t	i;

	while (!rf.eof())
	{
		getline(rf, line);
		if (line.compare(0, 5, "\tcgi:") == 0)
		{
			i = line.find(" ");
			line = line.substr(i + 1, line.length());
			if (line == "on")
				cgi = true;
			this->set_cgi_path(rf);
			return ;
		}
	}
}

void	Pserver::set_method(std::ifstream &rf)
{
	std::string	line;
	size_t	GIT;
	size_t	DELETE;
	size_t	POST;
	while (!rf.eof())
	{
		getline(rf, line);
		if (line.compare(0, 8, "\tmethods") == 0)
		{
			GIT = line.find("GIT");
			DELETE = line.find("DELETE");
			POST = line.find("POST");
			if (GIT == std::string::npos || DELETE == std::string::npos || POST == std::string::npos)
				throw (SyntaxError());
			this->methods[0] = line.substr(GIT, 3);
			this->methods[1] = line.substr(POST, 4);
			this->methods[2] = line.substr(DELETE, 6);
			this->set_cgi (rf);
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
			std::cout << line << std::endl;
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