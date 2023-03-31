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
		std::map<std::string, std::string> config_items;
	public : 
		std::string	index_val;
		std::string	location_val;
		std::string	upload_val;
		bool upload;
		std::string	autoindex_val;
		bool	autoindex;
		std::string	body_size;
		Location();
		std::string		getData(void) const;
	
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

		void	set_location(std::ifstream &rf);
		std::string	get_location(void) const;

		void	set_root(std::ifstream &rf);
		std::string	get_root(void) const;

		void	set_index(std::ifstream &rf);
		std::string	get_index(void) const;

		void	set_autoindex(std::ifstream &rf);
		std::string	get_autoindex(void) const;

		void	set_upload(std::ifstream &rf);
		std::string	get_upload(void) const;

		void	set_body_size(std::ifstream &rf);
		std::string	get_body_size(void) const;

		std::string	set_values(std::string line);
		void	set_config_items(void);

		std::map<std::string, std::string>	get_config_item(void) const;
		virtual ~Location();
};
#endif