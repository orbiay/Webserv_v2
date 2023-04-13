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
#include"../client.hpp"

void	cgi(Pserver &s, Client &c);
int	cgi_post(Pserver &s, Client &c, char **env);

int parsing(int argc, char **argv, char **env)
{
	if (argc == 2)
	{
		Client c_c;
		(void)env;
		(void)argc;
		Config c(argv);
		if (cgi_post(c.s[0], c_c, env) == 1)
			return (1);
		return (0);
	}
	return (1);
}