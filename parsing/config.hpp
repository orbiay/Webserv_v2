/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomman <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:50:35 by aomman            #+#    #+#             */
/*   Updated: 2023/03/19 15:50:37 by aomman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP
# include"location.hpp"
# include"Webserv.hpp"

class Config
{
	private :
		Config();
	public : 
		int	host;
		int	port;
		bool upload;
		std::string	root;
		std::string	index;
		std::string	location;
		std::vector<Pserver> s;
		static int nserv;
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
		void	set_loc_conf(char **argv);
		int	get_host() const;
		int	get_port() const;
		bool	get_upload() const;
		std::string	get_root() const;
		std::string	get_index() const;
		std::string	get_location() const;
		void	check_yml(char *str);
		~Config();
};
#endif