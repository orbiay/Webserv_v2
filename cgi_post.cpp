/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_post.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:34:45 by aomman            #+#    #+#             */
/*   Updated: 2023/04/13 13:44:09 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing/config.hpp"
#include"parsing/Webserv.hpp"
#include"client.hpp"

int	cgi_post(Pserver &s, Client &c, char **envm = NULL)
{
	(void)c;
	std::map<std::string, std::string> env;

	// env["HTTP_COOKIE"] = 
	env["GATEWAY_INTERFACE"] = "CGI/1.1";
	env["DOCUMENT_ROOT"] = s.L[0].root_val;
	env["HTTP_HOST"] = s.host;
	env["REQUEST_METHOD"] = "POST";
	env["REQUEST_URI"] = s.cgi_path;
	env["SCRIPT_FILENAME"] = s.cgi_path;
	env["SERVER_ADMIN"] = "abdelilahoma@gmail.com";
	env["SERVER_PORT"] = s.ports;
	env["SERVER_PROTOCOL"] = "HTTP/1.1";
	std::map<std::string, std::string>::iterator it;
	std::string	envp[10];
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
	while (i <= j)
	{
		envm[i] = (char *)envp[i].c_str();
		// std::cout << envm[i] << std::endl;
		i++;
	}
	std::string	line;
	std::ifstream f (s.cgi_path);
	if (!f.is_open())
	{
		std::cout << "Unable to open file\n";		
		return (1);
	}
	std::ofstream body("rendom.txt", std::ios::out);
	struct stat buff;
	int	st = stat (s.cgi_path.c_str(), &buff);
	// std::cout << "------------>" << buff.st_size << std::endl;
	(void)st;
    if (!f.is_open())
    {
        std::cout << "Unable to open file\n";
        return 1;
    }
    f.seekg(0, std::ios::end);
    std::streamsize size = f.tellg();
    f.seekg(0, std::ios::beg);

    char* buffer = new char[size];
    bool found_rn = false;
    std::streamsize count = 0;
    while (!found_rn && count < size)
    {
        f.read(buffer + count, 1);
        if (count > 0 && buffer[count - 1] == '\r' && buffer[count] == '\n')
        {
            found_rn = true;
            count++;
		}
		else
			count++;
    }
	std::string output;
	if (found_rn == 1)
	{
		std::streamsize remains = size - count;
		char *ramain_buff = new char[remains];
		f.read(ramain_buff, remains);
		std::string remaining_content(ramain_buff, remains);
		output = remaining_content;
		// std::cout << remaining_content << std::endl;
		delete []ramain_buff;
	}
    // std::cout.write (buffer, count);
	int	fd[2];
	char	*argc_s[3];
	argc_s[0] = (char *)"/usr/bin/php";
	argc_s[1] = (char *)s.cgi_path.c_str();
	argc_s[2] = NULL;
	if (access(argc_s[1], F_OK) == 0)
	{
		pipe(fd);
		if (fork() == 0)
		{
			int	a;

			a = 12;
			close(fd[0]);
			dup2 (fd[1], STDOUT_FILENO);
			write (fd[1], &a, sizeof (int));
			if (execve(argc_s[0], argc_s, envm) == -1)
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
	}
	return (0);
	delete[] buffer;
    f.close();
}
