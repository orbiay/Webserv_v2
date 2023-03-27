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
	this->upload = false;
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
	std::map<std::string, std::string>::iterator it;
	s[0].set_host(rf);
	s[0].set_nLocation(f);
	std::cout << s[0].get_host() << std::endl;
	std::cout << s[0].get_port() << std::endl;
	std::cout << s[0].methods[0] << std::endl;
	std::cout << s[0].methods[1] << std::endl;
	std::cout << s[0].methods[2] << std::endl;
	s[0].l[0].set_location(rf);
	s[0].l[0].set_config_items();
	config = s[0].l[0].get_config_item();
	it = config.begin();
	while (it != config.end())
	{
		std::cout << it->first << ","<< it->second << std::endl;
		++it;
	}
	std::cout << ">>>>>>>>location 2<<<<<<<<<<<" << std::endl;
	s[0].l[1].set_location(rf);
	s[0].l[1].set_config_items();
	config = s[0].l[1].get_config_item();
	it = config.begin();
	while (it != config.end())
	{
		std::cout << it->first << ","<< it->second << std::endl;
		++it;
	}
	std::cout << ">>>>>>>>>>>>>>server 1<<<<<<<<<<<" << std::endl;
	s[1].set_host(rf);
	s[1].set_nLocation(f);
	std::cout << s[1].get_host() << std::endl;
	std::cout << s[1].get_port() << std::endl;
	std::cout << s[1].methods[0] << std::endl;
	std::cout << s[1].methods[1] << std::endl;
	std::cout << s[1].methods[2] << std::endl;
	s[1].l[0].set_location(rf);
	s[1].l[0].set_config_items();
	config = s[1].l[0].get_config_item();
	it = config.begin();
	while (it != config.end())
	{
		 std::cout << it->first << ","<< it->second << std::endl;
		++it;
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
