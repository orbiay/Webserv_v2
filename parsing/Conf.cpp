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
	this->set_loc_conf(argv);
	this->check_yml(argv[1]);
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

void	Config::check_yml(char *str)
{
	size_t	i;

	std::string s(str);
	i = s.find(".yml");
	if (i == std::string::npos)
		throw (YmlFileError());
	std::ifstream f(str);
	int	len;

	f.seekg(0, f.end);
	len = f.tellg();
	if (len == 0)
		throw (Nofile());
	return ;
}

int	count_servers(char **argv)
{
	std::string	server;
	int			n_servr;
	std::ifstream file(argv[1], std::ios::in);
	if (file.is_open() == false)
	{
		file.close();
		throw ("Error");
	}
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

void	Config::set_loc_conf(char **argv)
{
	std::map<std::string, std::string> config;
	std::string	line;
	int			n_servr;
	std::ifstream rf(argv[1], std::ios::in);
	std::ifstream f(argv[1]);
	if (rf.is_open() == false)
	{
		rf.close();
		throw (NotOpen());
	}
	n_servr = count_servers(argv);
	Pserver s1;
	s1.set_nserv(rf);
	if (s1.get_nserv() != n_servr)
		return ;
	Pserver s[s1.get_nserv()];
	int	i;
	int	j;

	i = 0;
	Location l;
	while (i < s1.get_nserv())
	{
		j = 0;
		s[i].set_host(rf);
		s[i].set_nLocation(f);
		while (j < s[i].nloc)
		{
			l.set_location(rf);
			s[i].L.push_back(l);
			j++;
		}
		this->s.push_back(s[i]);
		i++;
	}
	rf.close();
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
