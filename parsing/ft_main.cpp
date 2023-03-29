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

int parsing(int argc, char **argv)
{
	if (argc == 2)
	{
		(void)argv;
		try
		{
			Config c(argv);

			std::cout<<c.Conf[0].l[0].get_location() << std::endl;
			std::cout<<c.Conf[0].l[1].get_location() << std::endl;
			std::cout<<c.Conf[1].l[0].get_location() << std::endl;
		}
		catch(std::exception &e)
		{
			std::cout << "Error : " << e.what() << std::endl;
		}
	}
	return (0);
}