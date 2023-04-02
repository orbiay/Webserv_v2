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

Config parsing(int argc, char **argv)
{
	if (argc == 2)
	{
		Config c(argv);
		try
		{

			std::cout<<c.s[0].L[0].get_error_pages()[0] << std::endl;
			std::cout<<c.s[0].L[1].get_error_pages()[0] << std::endl;
			std::cout<<c.s[0].L[2].get_error_pages()[0] << std::endl;
			std::cout<<c.s[1].L[0].get_error_pages()[0] << std::endl;
		}
		catch(std::exception &e)
		{
			std::cout << "Error : " << e.what() << std::endl;
		}
		return (c);
	}
	exit(1);
}