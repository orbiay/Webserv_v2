/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomman <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 00:44:53 by aomman            #+#    #+#             */
/*   Updated: 2023/03/26 00:44:54 by aomman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"config.hpp"

Config::Config()
{
}

Config::Config(char **argv)
{
	this->check_yml(argv[1]);
	this->set_loc_conf(argv);
}

const char	*Config::Nofile::what() const throw()
{
	return ("no server reached");
}

const char	*Config::NotOpen::what() const throw()
{
	return ("file not found");
}

const char	*Config::YmlFileError::what() const throw()
{
	return ("configuration file must be .yml");
}

const char	*Config::SyntaxError::what() const throw()
{
	return ("Syntax Error");
}

void	Config::check_yml(char *str)
{
	size_t	i;

	std::string s(str);
	i = s.find(".yml");
	if (i == std::string::npos || i != s.length() - 4)
		throw (YmlFileError());
	std::ifstream f(str);
	if (f.is_open() == false)
		throw (Nofile());
	return ;
}

void	Config::set_body_size(std::ifstream &rf)
{
	std::string	line;
	size_t	i;

	while (!rf.eof())
	{
		getline(rf, line);
		if (line.compare(0, 9, "body_size") == 0)
		{
			i = line.find(" ");
			line = line.substr(i + 1, line.length());
			std::stringstream stream(line);
			stream >> this->body_size;
			return ;
		}
	}
}

int	count_servers(char **argv)
{
	std::string	server;
	int			n_servr;
	std::ifstream file(argv[1], std::ios::in);
	if (file.is_open() == false)
		throw ("Error");
	n_servr = 0;
	while (!file.eof())
	{
		getline(file, server);
		if (server == "server:")
			n_servr++;
	}
	file.close();
	return (n_servr);
}

void	Config::set_conf_nserv()
{
	this->nserv = s.size();
}

void	Config::set_loc_conf(char **argv)
{
	std::map<std::string, std::string> config;
	std::string	line;
	int			n_servr;
	std::ifstream rf(argv[1], std::ios::in);
	std::ifstream f(argv[1]);
	std::ifstream f2(argv[1]);
	if (rf.is_open() == false || f.is_open() == false || f2.is_open() == false)
	{
		rf.close();
		f.close();
		f2.close();
		throw (NotOpen());
	}
	n_servr = count_servers(argv);
	Pserver s1;
	this->set_body_size(f2);
	s1.set_nserv(rf);
	s1.set_end(f2);
	if (s1.get_nserv() != n_servr)
		throw (SyntaxError());
	if (s1.end != n_servr)
		throw (SyntaxError());
	Pserver s[s1.get_nserv()];
	int	i;
	int	j;

	i = 0;
	Location *l = new Location();
	while (i < s1.get_nserv())
	{
		j = 0;
		s[i].set_host(rf);
		s[i].set_nLocation(f);
		if (s[i].nloc != s[i].lend)
			throw (SyntaxError());
		while (j < s[i].nloc)
		{
			l->set_location(rf);
			l->check_errors();
			s[i].L.push_back(l[0]);
			j++;
		}
		this->s.push_back(s[i]);
		i++;
	}
	delete l;
	this->set_conf_nserv();
	rf.close();
	f.close();
	f2.close();
}

int	Config::get_host() const
{
	return (this->host);
}

int	Config::get_port() const
{
	return (this->port);
}

bool	Config::get_upload() const
{
	return (this->upload);
}

std::string	Config::get_root() const
{
	return (this->root);
}

std::string	Config::get_index() const
{
	return (this->index);
}

std::string	Config::get_location() const
{
	return (this->location);
}


Config::~Config(){}
