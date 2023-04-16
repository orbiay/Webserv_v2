/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:40:01 by aomman            #+#    #+#             */
/*   Updated: 2023/04/15 23:43:05 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"config.hpp"
#include"Webserv.hpp"
#include"../client.hpp"

void	cgi(Pserver &s, Client &c);
int	cgi_post(Pserver &s, Client &c, char **env);

int parsing(int argc, char **argv, char **env)
{
	if (argc == 2)
	{
		(void)env;
		(void)argc;
		(void)argv;
		// Config c(argv);
		// std::cout << c.s[0].L[0].cgi << std::endl;
		// std::cout << c.s[0].L[0].autoindex << std::endl;
		// std::cout << c.s[0].L[1].autoindex << std::endl;
		// std::cout << c.s[0].L[2].autoindex << std::endl;
		//exit (0);
	}
	return (0);
}