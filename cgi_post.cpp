/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_post.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomman <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:34:45 by aomman            #+#    #+#             */
/*   Updated: 2023/04/11 17:34:46 by aomman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing/config.hpp"
#include"parsing/Webserv.hpp"
#include"client.hpp"

int	cgi_post(Pserver &s, Client &c, char **envm)
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
		std::cout << envm[i] << std::endl;
		i++;
	}
	std::string	line;
	std::ifstream f (s.cgi_path);
	std::ofstream body("random.txt", std::ios::out);
    if (!f.is_open())
    {
        std::cout << "Unable to open file" << std::endl;
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
	if (found_rn == 1)
	{
		std::streamsize remains = size - count;
		char *ramain_buff = new char[remains];
		f.read(ramain_buff, remains);
		std::string remaining_content(ramain_buff, remains);
		body << remaining_content;
		delete []ramain_buff;
	}
    //std::cout.write (buffer, count);
	int	fd[2];
	char	*argc_s[3];
	std::cout << s.cgi_extention << std::endl;
	if (s.cgi_extention == "php")
		argc_s[0] = (char *)"/usr/bin/php";
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
	body.close();
}
