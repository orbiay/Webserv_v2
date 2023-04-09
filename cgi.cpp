/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomman <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:26:07 by aomman            #+#    #+#             */
/*   Updated: 2023/04/05 20:26:08 by aomman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing/config.hpp"

void	cgi(Config c)
{
	int	fd[2];
	char	*argc_s[3];
	argc_s[0] = (char *)"/usr/bin/php";
	argc_s[1] = (char *)c.s[1].L[0].cgi_path.c_str();
	argc_s[2] = NULL;
	pipe(fd);
	if (fork() == 0)
	{
		int	a;

		a = 12;
		close(fd[0]);
		dup2 (fd[1], STDOUT_FILENO);
		write (fd[1], &a, sizeof (int));
		if (execve(argc_s[0], argc_s, NULL) == -1)
		{
			std::cout << "execve : error" << std::endl;
			exit (1);
		}
		close (fd[1]);
	}
	int	b;
	close (fd[1]);
	dup2 (fd[0], STDIN_FILENO);
	read (fd[0], &b, sizeof(int));
	close (fd[0]);
	std::cout << "--> " << b << std::endl;
}
