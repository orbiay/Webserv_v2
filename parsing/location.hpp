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
# include<sstream>

class Location
{
	public : 
		int			status;
		bool		upload;
		bool		autoindex;
		bool		cgi;
		std::string file_name;
		std::string	root_val;
		std::string line_val;
		std::string	index_val;
		std::string	location_val;
		std::string	upload_val;
		std::string	status_str;
		std::string	redirec;
		std::string	autoindex_val;
		std::string	body_size;
		std::string	error_path;
		std::string	cgi_path;
		std::string cgi_extention;
		std::vector<std::string> error_cods;
		std::vector<std::string>files_path;
		Location();
	
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

		void	set_index(std::string);
		std::string	get_index(void) const;

		void	set_autoindex(std::string);
		std::string	get_autoindex(void) const;

		void	set_upload(std::string);
		bool	get_upload(void) const;


		std::string	get_body_size(void) const;

		void	set_redirection(std::string);
		std::string get_redirection(void) const;
		int	get_status(void) const;

		std::string	set_values(std::string line);
		void	set_config_items(void);

		void	set_error_pages(std::string);
		std::vector<std::string>	get_error_pages(void) const;

		void	set_error_path(std::string);
		std::string	get_error_path(void) const;

		void	set_cgi(std::string line);
		void	set_cgi_path(std::string line);
		void	check_errors(void) const;

		virtual ~Location();
};
#endif