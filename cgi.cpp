/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomman <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 00:28:59 by aomman            #+#    #+#             */
/*   Updated: 2023/04/15 00:29:00 by aomman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"CGI.hpp"

CGI::~CGI(){}
CGI::CGI(){}

int	CGI::cgi(Pserver &s, Client &c)
{
	(void)c;
	int	fd[2];
	char	*argc_s[3];
	argc_s[0] = (char *)"/Users/aomman/Desktop/Webserv_v2/php-cgi";
	argc_s[1] = (char *)s.cgi_path.c_str();
	argc_s[2] = NULL;
	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		close (fd[1]);
		dup2 (c.file, STDIN_FILENO);
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
	return (0);
}

int	CGI::cgi(Pserver &s, Client &c, char **envm)
{
	std::map<std::string, std::string> env;
	env["HTTP_ACCEPT"] = c.parse._data["Accept"];
	env["HTTP_ACCEPT_ENCODING"] = c.parse._data["Accept-Encoding"];
	env["HTTP_HOST"] = c.parse._data["Host"];
	env["GATEWAY_INTERFACE"] = "CGI/1.1";
	env["DOCUMENT_ROOT"] = s.L[0].root_val;
	env["REQUEST_METHOD"] = "POST";
	env["REQUEST_URI"] = s.cgi_path;
	env["SCRIPT_FILENAME"] = s.cgi_path;
	env["SERVER_ADMIN"] = "abdelilahoma@gmail.com";
	env["SERVER_PORT"] = s.ports;
	env["SERVER_PROTOCOL"] = "HTTP/1.1";
	std::map<std::string, std::string>::iterator it;
	std::string	envp[12];
	it = env.begin();
	int	i;
	int	j = 0;
	std::string eq = "=";
	i = 0;
	while (it != env.end())
	{
		envp[i] = it->first + "=" + it->second;
		i++;
		j++;
		++it;
	}
	i = 0;
	j--;
	while (i <= j && envm != NULL)
	{
		envm[i] = (char *)envp[i].c_str();
		i++;
	}
	std::cout << s.cgi_path << std::endl;
	std::ifstream f(s.cgi_path);
	if (!f.is_open())
	{
		std::cout << "Unable to open file" << std::endl;		
		return (1);
	}
	int	fd[2];
	char	*argc_s[3];
	std::cout << s.cgi_extention << std::endl;
	if (s.cgi_extention == "php")
		argc_s[0] = (char *)"Users/aomman/Desktop/Webserv_v2/php-cgi";
	if (s.cgi_extention == "cpp")
		argc_s[0] = (char *)"/usr/bin/c++";
	if (s.cgi_extention == "js")
		argc_s[0] = (char *)"/usr/bin/node";
	if (s.cgi_extention == "py")
		argc_s[0] = (char *)"/usr/bin/python";
	if (s.cgi_extention == "c")
		argc_s[0] = (char *)"/usr/bin/gcc";
	argc_s[1] = (char *)s.cgi_path.c_str();
	argc_s[2] = NULL;
	int	tmp_fd = open("rand", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (access(argc_s[1], F_OK) == 0)
	{
		pipe(fd);
		if (fork() == 0)
		{
			close(fd[1]);
			dup2 (c.file, STDIN_FILENO);
			close(c.file);
			dup2 (tmp_fd, STDOUT_FILENO);
			close (tmp_fd);
			close (fd[0]);
			execve(argc_s[0], argc_s, envm);
			std::cerr << "error in execve" << std::endl;
		}
		close (fd[0]);
		close (fd[1]);
		dup2 (fd[0], STDIN_FILENO);
	}
	this->filename = tmp_fd;
    f.close();
	return (this->filename);
}
