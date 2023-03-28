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
		int			nserv;
		std::string	host;
		int			port;
	public :
		static int	nloc;
		std::string methods[3];
		Location l[100];
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
		~Pserver();
};

#endif
