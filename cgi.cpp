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
	std::map<std::string, std::string> env;
	env["REDIRECT_STATUS"] = "200";
	env["HTTP_ACCEPT"] = c.parse._data["Accept"];
	env["HTTP_ACCEPT_ENCODING"] = c.parse._data["Accept-Encoding"];
	env["HTTP_HOST"] = c.parse._data["Host"];
	env["GATEWAY_INTERFACE"] = "CGI/1.1";
	env["DOCUMENT_ROOT"] = c.location.root_val;
	env["REQUEST_METHOD"] = "GET";
	env["REQUEST_URI"] = c.location.cgi_path;
	env["SCRIPT_FILENAME"] = c.location.cgi_path;
	env["SERVER_ADMIN"] = "abdelilahoma@gmail.com";
	env["SERVER_PORT"] = s.ports;
	env["SERVER_PROTOCOL"] = "HTTP/1.1";
	env["HTTP_COOKIE"] = c.parse._data["Cookie"];
	std::map<std::string, std::string>::iterator it;
	std::string	envp[env.size()];
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
	char **envm;
	envm = new char *[env.size() + 1];
	while (i < j)
	{
		envm[i] = (char *)envp[i].c_str();
		i++;
	}
	envm[i] = NULL;
	std::ifstream f(c.location.cgi_path);
	if (!f.is_open())
	{
		std::cout << "Unable to open file" << std::endl;		
		return (1);
	}
	int	fd[2];
	char	*argc_s[3];
	std::cout << s.L[0].cgi_extention << std::endl;
	if (s.L[0].cgi_extention == "php")
		argc_s[0] = (char *)"/Users/aomman/Desktop/Webserv_v2/php-cgi";
	if (s.L[0].cgi_extention == "cpp")
		argc_s[0] = (char *)"/usr/bin/c++";
	if (s.L[0].cgi_extention == "js")
		argc_s[0] = (char *)"/usr/bin/node";
	if (s.L[0].cgi_extention == "py")
		argc_s[0] = (char *)"/usr/bin/python";
	if (s.L[0].cgi_extention == "c")
		argc_s[0] = (char *)"/usr/bin/gcc";
	argc_s[1] = (char *)s.L[0].cgi_path.c_str();
	argc_s[2] = NULL;
	int	tmp_fd = open("rand", O_CREAT | O_RDWR, 0644);
	int	fd_cline = open(c.file_name.c_str(), std::ios::in);
	if (access(argc_s[1], F_OK) == 0)
	{
		pipe(fd);
		if (fork() == 0)
		{
			close(fd[1]);
			dup2 (fd_cline, STDIN_FILENO);
			close(fd_cline);
			dup2 (tmp_fd, STDOUT_FILENO);
			dup2 (tmp_fd, STDERR_FILENO);
			close (tmp_fd);
			close (fd[0]);
			execve(argc_s[0], argc_s, envm);
			std::cerr << "error in execve" << std::endl;
		}
		close (fd[0]);
		close (fd[1]);
		dup2 (fd[0], STDIN_FILENO);
	}
	i = 0;
	while (envm[i])
	{
		delete []envm[i];
		i++;	
	}
	delete []envm;
    f.close();
	return (0);
}

int	CGI::cgi(Pserver &s, Client &c, char **envm)
{
	std::map<std::string, std::string> env;
	env["CONTENT_LENGTH"] = c.parse._data["Content-Length"];
	env["CONTENT_TYPE"] = c.parse._data["Content-Type"];
	env["REDIRECT_STATUS"] = "200";
	env["HTTP_ACCEPT"] = c.parse._data["Accept"];
	env["HTTP_ACCEPT_ENCODING"] = c.parse._data["Accept-Encoding"];
	env["HTTP_HOST"] = c.parse._data["Host"];
	env["GATEWAY_INTERFACE"] = "CGI/1.1";
	env["DOCUMENT_ROOT"] = c.location.root_val;
	env["REQUEST_METHOD"] = "POST";
	env["REQUEST_URI"] = c.location.cgi_path;
	env["SCRIPT_FILENAME"] = c.location.cgi_path;
	env["SERVER_ADMIN"] = "abdelilahoma@gmail.com";
	env["SERVER_PORT"] = s.ports;
	env["SERVER_PROTOCOL"] = "HTTP/1.1";
	env["HTTP_COOKIE"] = c.parse._data["Cookie"];
	std::map<std::string, std::string>::iterator it;
	std::string	envp[env.size()];
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
	envm = new char *[env.size() + 1];
	while (i < j)
	{
		envm[i] = (char *)envp[i].c_str();
		i++;
	}
	envm[i] = NULL;
	std::ifstream f(c.location.cgi_path);
	if (!f.is_open())
	{
		std::cout << "Unable to open file" << std::endl;		
		return (1);
	}
	int	fd[2];
	char	*argc_s[3];
	std::cout << s.L[0].cgi_extention << std::endl;
	if (s.L[0].cgi_extention == "php")
		argc_s[0] = (char *)"/Users/aomman/Desktop/Webserv_v2/php-cgi";
	if (s.L[0].cgi_extention == "cpp")
		argc_s[0] = (char *)"/usr/bin/c++";
	if (s.L[0].cgi_extention == "js")
		argc_s[0] = (char *)"/usr/bin/node";
	if (s.L[0].cgi_extention == "py")
		argc_s[0] = (char *)"/usr/bin/python";
	if (s.L[0].cgi_extention == "c")
		argc_s[0] = (char *)"/usr/bin/gcc";
	argc_s[1] = (char *)s.L[0].cgi_path.c_str();
	argc_s[2] = NULL;
	int	tmp_fd = open("rand", O_CREAT | O_RDWR, 0644);
	int	fd_cline = open(c.file_name.c_str(), std::ios::in);
	if (access(argc_s[1], F_OK) == 0)
	{
		pipe(fd);
		if (fork() == 0)
		{
			close(fd[1]);
			dup2 (fd_cline, STDIN_FILENO);
			close(fd_cline);
			dup2 (tmp_fd, STDOUT_FILENO);
			dup2 (tmp_fd, STDERR_FILENO);
			close (tmp_fd);
			close (fd[0]);
			execve(argc_s[0], argc_s, envm);
			std::cerr << "error in execve" << std::endl;
		}
		close (fd[0]);
		close (fd[1]);
		dup2 (fd[0], STDIN_FILENO);
	}
	//i = 0;
	//while (envm[i])
	//{
	//	delete []envm[i];
	//	i++;	
	//}
	//delete []envm;
    f.close();
	return (0);
}
