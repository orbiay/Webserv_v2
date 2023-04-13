/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomman <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:55:20 by aomman            #+#    #+#             */
/*   Updated: 2023/03/11 14:55:21 by aomman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP
#include"location.hpp"
# include <new>

class Pserver
{
	private :
		std::string	server;
	public :
		std::string	host;
		std::string	ports;
		int			nserv;
		int			port;
		int			nloc;
		int			end;
		int			lend;
		bool		cgi;
		std::string	cgi_path;
		std::string cgi_extention;
		std::string methods[3];


		std::vector<Location> L;
		Pserver();

		class SyntaxError : public std::exception
		{
			virtual const char* what() const throw();
		};
		void	set_host(std::ifstream &rf);
		std::string	get_host(void) const;
		int			get_port(void) const;

		void	set_nLocation(std::ifstream &f);
		void	set_method(std::ifstream &rf);

		void	set_nserv(std::ifstream &rf);
		int		get_nserv(void) const;

		void	set_cgi(std::ifstream &rf);
		void	set_cgi_path(std::ifstream &rf);

		void	set_end(std::ifstream &f2);
		~Pserver();
};

#endif
