/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:40:01 by aomman            #+#    #+#             */
/*   Updated: 2023/04/16 20:46:42 by fbouanan         ###   ########.fr       */
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
		Config c(argv);
		std::cout << c.s[0].L[1].methods[0] << std::endl;
	}
	return (0);
}