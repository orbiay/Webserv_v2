/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomman <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:14:08 by aomman            #+#    #+#             */
/*   Updated: 2023/03/16 17:14:10 by aomman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP
# include<iostream>
# include<fstream>
# include<exception>
# include<vector>
# include<algorithm>
# include<map>
# include<stdlib.h>

class Location
{
	private : 
		std::string file_name;
		std::string	root_val;
		std::string line_val;
		std::string	index_val;
		std::string	location_val;
		std::string	host;
		std::string	port;
		std::string	upload_val;
		std::map<std::string, std::string> config_items;
	public : 
		Location();
		Location(const Location &ws);
		Location operator = (const Location &ws);
		void	setNginixFile(std::ifstream &rf, char *str);
		std::string		getData(void) const;
		class	NotOpen : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};
		class	EndNotReached : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};
		class	Nofile : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};
		class	YmlFileError : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};
		class	PathError : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};
		class	SyntaxError : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};
		void	check_yml(char *str);
		void	check_serverfile(std::ifstream &rf);
		void	ft_getserver(std::ifstream &rf);

		void	set_root(std::ifstream &rf);
		std::string	get_root(void) const;

		void	set_index(std::ifstream &rf);
		std::string	get_index(void) const;

		void	set_upload(std::ifstream &rf);
		std::string	get_upload(void) const;

		void	set_location(std::ifstream &rf);
		std::string	get_location(void) const;

		std::string	set_values(std::string line);
		void	set_config_items(void);

		std::map<std::string, std::string>	get_config_item(void) const;
		virtual ~Location();
};
#endif