/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:50:35 by aomman            #+#    #+#             */
/*   Updated: 2023/04/14 22:57:55 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP
# include"location.hpp"
# include"Webserv.hpp"
# include <unistd.h>
# include <new>
# include <string>
# include "../http.hpp"

class Config
{
	private :
		Config();
	public : 
		int	host;
		int	port;
		
		bool upload;
		size_t		body_size;
		std::string	root;
		std::string	index;
		std::string	location;
		std::vector<Pserver> s;
		int nserv;
		Config(char **argv);

		class	Nofile : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};
		class	NotOpen : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};
		class	YmlFileError : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};
		class	SyntaxError : public std::exception
		{
			public :
				virtual const char *what() const throw();
		};
		void	set_loc_conf(char **argv);

		void	set_conf_nserv();
		int	get_host() const;
		int	get_port() const;
		bool	get_upload() const;
		std::string	get_root() const;
		std::string	get_index() const;
		std::string	get_location() const;
		void	check_yml(char *str);
		void	set_body_size(std::ifstream &rf);
		void	server_methods(Pserver serv);
		~Config();
};
#endif