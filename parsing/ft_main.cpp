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

void	cgi(Pserver &s);

int parsing(int argc, char **argv)
{
	if (argc == 2)
	{
		(void)argc;
		Config c(argv);
		std::cout << c.s[1].L[0].error_cods[0] << std::endl;
		std::cout << c.s[0].L[0].index_val << std::endl;
		std::cout << c.s[0].L[0].autoindex << std::endl;
		std::cout << c.s[0].L[1].root_val << std::endl;
		std::cout << c.s[0].L[1].autoindex << std::endl;
		std::cout << c.s[0].L[1].index_val << std::endl;
		std::cout << c.s[0].L[2].index_val << std::endl;
		std::cout << c.s[0].L[2].upload << std::endl;
		std::cout << c.s[0].port << std::endl;
		cgi(c.s[0]);
		return (0);
	}
	return (1);
}