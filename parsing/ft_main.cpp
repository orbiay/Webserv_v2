/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:40:01 by aomman            #+#    #+#             */
/*   Updated: 2023/03/19 14:10:00 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"config.hpp"
#include"Webserv.hpp"

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

int parsing(int argc, char **argv)
{
	if (argc == 2)
	{
		(void)argv;
		try
		{
			std::map<std::string, std::string> config;
			std::string	line;
			int			n_servr;

			std::ifstream rf(argv[1], std::ios::in);
			if (rf.is_open() == false)
			{
				rf.close();
				throw ("not opened");
			}
			n_servr = count_servers(argv);
			Pserver s1;
			Config cnf;
			cnf.set_loc_conf();
			s1.set_nserv(rf);
			if (s1.get_nserv() != n_servr)
				return (1);
			Pserver s[s1.get_nserv()];
			std::map<std::string, std::string>::iterator it;
			// std::cout << ">>>>>>>>>location 1 <<<<<<<<<" << std::endl;
			s[0].l[0].set_host(rf, argv[1]);
			s[0].l[0].set_config_items();
			config = s[0].l[0].get_config_item();
			it = config.begin();
			while (it != config.end())
			{
				//std::cout << it->first << ","<< it->second << std::endl;
				++it;
			}
			//std::cout << ">>>>>>>>location 2<<<<<<<<<<<" << std::endl;
			s[0].l[1].set_host(rf, argv[1]);
			s[0].l[1].set_config_items();
			config = s[0].l[1].get_config_item();
			it = config.begin();
			while (it != config.end())
			{
				//std::cout << it->first << ","<< it->second << std::endl;
				++it;
			}
			//std::cout << ">>>>>>>>>>>>>>server 1<<<<<<<<<<<" << std::endl;
			s[1].l[0].set_host(rf, argv[1]);
			s[1].l[0].set_config_items();
			config = s[1].l[0].get_config_item();
			it = config.begin();
			while (it != config.end())
			{
				// std::cout << it->first << ","<< it->second << std::endl;
				++it;
			}
			rf.close();
		}
		catch(std::exception &e)
		{
			std::cout << "Error : " << e.what() << std::endl;
		}
	}
	return (0);
}