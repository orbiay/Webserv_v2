/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomman <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:17:29 by aomman            #+#    #+#             */
/*   Updated: 2023/04/17 23:17:32 by aomman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"CGI.hpp"
#include<sys/wait.h>

CGI::~CGI(){}
CGI::CGI(){}

int	CGI::cgi(Pserver &s, Client &c)
{
	std::string line;
	std::stringstream cont(c.header);
	std::string holder;
	std::string Cnlengh;
	std::string http_accpet;
	std::string local_host;
	std::string cookie;
	if (c.flag_cgi == false)
	{
		while (!cont.eof())
		{
			getline(cont, line);
			if (line.compare(0, 5, "Host:") == 0)
			{
				size_t i = line.find(13);
				local_host = line.substr(6, i - 6);
			}
			if (line.compare(0, 7, "Accept:") == 0)
			{
				size_t i = line.find(13);
				http_accpet = line.substr(8, i - 8);
			}
			if (line.compare(0, 7, "Cookie:") == 0)
			{
				size_t i = line.find(13);
				cookie = line.substr(8, i - 8);
			}
		}
		c.env["REDIRECT_STATUS"] = "200";
		c.env["HTTP_ACCEPT"] = http_accpet;
		c.env["HTTP_ACCEPT_ENCODING"] = c.parse._data["Accept-Encoding"];
		c.env["HTTP_HOST"] = local_host;
		c.env["GATEWAY_INTERFACE"] = "CGI/1.1";
		c.env["DOCUMENT_ROOT"] = c.location.root_val;
		c.env["REQUEST_METHOD"] = "GET";
		c.env["REQUEST_URI"] = c.location.cgi_path;
		c.env["SCRIPT_FILENAME"] = c.location.cgi_path;
		c.env["SERVER_ADMIN"] = "abdelilahoma@gmail.com";
		c.env["SERVER_PORT"] = s.ports;
		c.env["SERVER_PROTOCOL"] = "HTTP/1.1";
		c.env["PATH_INFO"] = c.location.root_val + c.location.location_val ;
		c.env["HTTP_COOKIE"] = cookie;
		c.flag_cgi = true;
	}
	std::map<std::string, std::string>::iterator it;
	std::string	envp[c.env.size()];
	it = c.env.begin();
	int	i;
	int	j = 0;
	std::string eq = "=";
	i = 0;
	while (it != c.env.end())
	{
		envp[i] = it->first + "=" + it->second;
		i++;
		j++;
		++it;
	}
	i = 0;
	char **envm;
	envm = new char *[c.env.size() + 1];
	while (i < j)
	{
		envm[i] = (char *)envp[i].c_str();
		i++;
	}
	envm[i] = NULL;
	std::cout << "|" <<c.location.cgi_path << "|" << std::endl;
	std::ifstream f(c.location.cgi_path);
	if (!f.good())
	{
		std::cout << "Unable to open file" << std::endl;
		return (1);
	}
	std::cout<< "|" << "heeeeeeer"<<c.location.cgi_extention << "|" << std::endl;
	int	fd[2];
	char	*argc_s[3];
	if (c.location.cgi_extention == "php")
		argc_s[0] = (char *)"/Users/aomman/Desktop/Webserv_v2/php-cgi";
	else if (c.location.cgi_extention == "cpp")
		argc_s[0] = (char *)"/usr/bin/c++";
	else if (c.location.cgi_extention == "c")
		argc_s[0] = (char *)"/usr/bin/gcc";
	else if (c.location.cgi_extention == "pl")
		argc_s[0] = (char *)"/usr/bin/perl";
	argc_s[1] = (char *)c.location.cgi_path.c_str();
	argc_s[2] = NULL;
	int	tmp_fd = open("rand", O_CREAT | O_RDWR | O_TRUNC , 0644);
	int	fd_cline = open(c.file_name.c_str(), std::ios::in);
	if (access(argc_s[1], F_OK) == 0)
	{
		std::cout << "heeeeeeer" << std::endl;
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
	while (waitpid(-1, NULL, WNOHANG) == 0)
		continue;
	
	close (tmp_fd);
	close(fd_cline);
	//i = 0;
	//while (envm[i])
	//{
	//	delete envm[i];
	//	i++;	
	//}
	delete []envm;
	envm = nullptr;
    f.close();
	return (0);
}

int	CGI::cgi(Pserver &s, Client &c, char **envm)
{
	std::string line;
	std::stringstream cont(c.header);
	std::string holder;
	std::string Cnlengh;
	std::string http_accpet;
	std::string local_host;
	std::string cookie;
	if (c.flag_cgi == false)
	{
		while (!cont.eof())
		{
			getline(cont, line);
			if (line.compare(0, 5, "Host:") == 0)
			{
				size_t i = line.find(13);
				local_host = line.substr(6, i - 6);
			}
			if (line.compare(0, 7, "Accept:") == 0)
			{
				size_t i = line.find(13);
				http_accpet = line.substr(8, i - 8);
			}
			if (line.compare(0, 13, "Content-Type:") == 0)
			{		
				size_t i = line.find(13);
				holder = line.substr(14, i - 14);
			}
			if (line.compare(0, 15, "Content-Length:") == 0)
			{
				size_t i = line.find(13);
				Cnlengh = line.substr(16, i - 16);
			}
			if (line.compare(0, 7, "Cookie:") == 0)
			{
				size_t i = line.find(13);
				cookie = line.substr(8, i - 8);
			}
		}
		c.env["CONTENT_LENGTH"] = Cnlengh;
		c.env["CONTENT_TYPE"] = holder;
		c.env["REDIRECT_STATUS"] = "200";
		c.env["HTTP_ACCEPT"] = http_accpet;
		c.env["HTTP_ACCEPT_ENCODING"] = c.parse._data["Accept-Encoding"];
		c.env["HTTP_HOST"] = local_host;
		c.env["GATEWAY_INTERFACE"] = "CGI/1.1";
		c.env["DOCUMENT_ROOT"] = c.location.root_val;
		c.env["REQUEST_METHOD"] = "POST";
		c.env["REQUEST_URI"] = c.location.cgi_path;
		c.env["SCRIPT_FILENAME"] = c.location.cgi_path;
		c.env["SERVER_ADMIN"] = "abdelilahoma@gmail.com";
		c.env["SERVER_PORT"] = s.ports;
		c.env["SERVER_PROTOCOL"] = "HTTP/1.1";
		c.env["PATH_INFO"] = c.location.root_val + c.location.location_val ;
		c.env["HTTP_COOKIE"] = cookie;
		c.flag_cgi = true;
	}
	std::map<std::string, std::string>::iterator it;
	std::string	envp[c.env.size()];
	it = c.env.begin();
	int	i;
	int	j = 0;
	std::string eq = "=";
	i = 0;
	while (it != c.env.end())
	{
		envp[i] = it->first + "=" + it->second;
		i++;
		j++;
		++it;
	}
	i = 0;
	envm = new char *[c.env.size() + 1];
	while (i < j)
	{
		envm[i] = (char *)envp[i].c_str();
		i++;
	}
	envm[i] = NULL;
	std::ifstream f(c.location.cgi_path);
	if (!f.good())
	{
		std::cout << "Unable to open file" << std::endl;		
		return (1);
	}
	int	fd[2];
	char	*argc_s[3];
	std::cout << "heeeeeeer"<<c.location.cgi_extention << std::endl;
	if (c.location.cgi_extention == "php")
		argc_s[0] = (char *)"/Users/aomman/Desktop/Webserv_v2/php-cgi";
	if (c.location.cgi_extention == "cpp")
		argc_s[0] = (char *)"/usr/bin/c++";
	if (c.location.cgi_extention == "py")
		argc_s[0] = (char *)"/usr/bin/python";
	if (c.location.cgi_extention == "c")
		argc_s[0] = (char *)"/usr/bin/gcc";
	argc_s[1] = (char *)c.location.cgi_path.c_str();
	argc_s[2] = NULL;
	std::cout << argc_s[0] << std::endl;
	std::cout << argc_s[1] << std::endl;
	int	tmp_fd = open("rand", O_CREAT | O_RDWR | O_TRUNC, 0644);
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
	waitpid(-1, NULL, WUNTRACED);
	close (tmp_fd);
	close(fd_cline);
	// i = 0;
	// while (envm[i])
	// {
	// 	delete []envm[i];
	// 	i++;	
	// }
	delete []envm;
	envm = nullptr;
    f.close();
	return (0);
}
