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
}

int	count_servers(char **argv)
{
	std::string	server;
	int			n_servr;
	std::ifstream file(argv[1], std::ios::in);
	if (file.is_open() == false)
	{
		file.close();
		throw ("not opened");
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
		throw ("not opened");
	}
	n_servr = count_servers(argv);
	Pserver s1;
	s1.set_nserv(rf);
	if (s1.get_nserv() != n_servr)
		return ;
	Pserver s[s1.get_nserv()];
	s[0].set_host(rf);
	s[0].set_nLocation(f);
	s[0].l[0].set_location(rf);
	s[0].l[0].set_config_items();
	s[0].l[1].set_location(rf);
	s[0].l[1].set_config_items();
	s[1].set_host(rf);
	s[1].set_nLocation(f);
	s[1].l[0].set_location(rf);
	s[1].l[0].set_config_items();
	//std::vector<Pserver>::iterator	it;
	this->Conf.push_back(s[0]);
	this->Conf.push_back(s[1]);
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
