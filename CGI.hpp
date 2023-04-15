/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomman <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 00:27:00 by aomman            #+#    #+#             */
/*   Updated: 2023/04/15 00:27:03 by aomman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP
# include"parsing/config.hpp"
# include"parsing/Webserv.hpp"
# include"client.hpp"
# include <fstream>

class	CGI
{
	public:
		CGI();
		//int	filename;
		int cgi(Pserver &s, Client &c, char **env);
		int	cgi(Pserver &s, Client &c);
		~CGI();
};
#endif
