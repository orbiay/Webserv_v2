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

void	cgi(Config c);

int parsing(int argc, char **argv)
{
	if (argc == 2)
	{
		(void)argc;
		try
		{
			Config c(argv);
			std::cout << c.s[0].L[0].cgi_extention << std::endl;
			std::cout << c.s[0].L[1].cgi_extention << std::endl;
			std::cout << c.s[0].L[2].cgi_extention << std::endl;
			std::cout << c.s[1].L[0].cgi_path << std::endl;
			cgi(c);
		}
		catch(std::exception &e)
		{
			std::cout << "Error : " << e.what() << std::endl;
		}
	}
	return (0);
}