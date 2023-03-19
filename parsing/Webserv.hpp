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

class Server
{
	private :
		std::string	server;
	public :
		Location l[100];
		Server();
		void	set_server(std::ifstream &file);
		std::string	get_server(void) const;
		~Server();
};

#endif
