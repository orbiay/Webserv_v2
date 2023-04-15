/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:20:30 by aomman            #+#    #+#             */
/*   Updated: 2023/04/15 01:11:58 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"location.hpp"

std::vector<std::string> split(const std::string& str, char delimiter = ' ')
{
    std::vector<std::string> parts;
    std::stringstream stream(str);
    std::string item;
    while (std::getline(stream, item, delimiter)) {
        if (!item.empty())
            parts.push_back(item);
    }
    if (parts.empty())
        parts.push_back(item);
    return (parts);
}

Location::Location()
{
}

const char *Location::PathError::what() const throw()
{
	return ("invalid path");
}

const char *Location::SyntaxError::what() const throw()
{
	return ("Syntax Error");
}

void	Location::check_errors(void) const
{
	if (this->root_val == ""
		|| this->location_val == ""
		|| this->upload_val == ""
		|| this->error_cods.size() == 0
		|| this->error_path == "")
		throw (SyntaxError());
	if ((this->cgi == true && this->upload == true) || (this->cgi == true && this->autoindex == true)
		|| (this->upload == true && this->autoindex == true))
		throw (SyntaxError());
	if (this->status != 301)
	{
		std::cout << this->status << std::endl;
		throw (SyntaxError());
	}
}

void	Location::set_cgi_path(std::string line)
{
	size_t	i;
	size_t	j;
	i = line.find("/");
	this->cgi_path = line.substr(i, line.length() - 7);
	j = line.find(" ");
	if (j == std::string::npos)
		return ;
	this->cgi_extention = line.substr(j + 1, line.length());
}

void	Location::set_cgi(std::string	line)
{
	size_t	i;
	i = line.find(" ");
	std::cout << "cgi" << std::endl;
	line = line.substr(i + 1, line.length());
	if (line == "on")
		cgi = true;
}

void	Location::set_error_path(std::string line)
{
	size_t		i;
	if (line == "\tlend")
		return ;
	i = line.find("/");
	this->error_path = line.substr(i, line.length());
}

std::string	Location::set_values(std::string line)
{
	size_t	start;
	start = line.find("/");
	if (start == std::string::npos)
		throw(SyntaxError());
	this->line_val = line.substr(start, line.length());
	return (this->line_val);
}

void	Location::set_error_pages(std::string line)
{
	size_t		i;
	i = line.find(" ");
	line = line.substr(i + 1, line.length());
	this->error_cods = split(line, ' ');
	//this->set_error_path(rf);
}

std::vector<std::string>	Location::get_error_pages(void) const
{
	return (this->error_cods);
}

void	Location::set_redirection(std::string line)
{
	size_t	i;
	size_t	j;
	i = line.find(" ");
	this->status_str = line.substr(i + 1, 3);
	this->status = std::atoi(this->status_str.c_str());
	j = line.find("/");
	this->redirec = line.substr(j, line.length());
	//this->set_error_pages(rf);
}

std::string	Location::get_redirection(void) const
{
	return (this->redirec);
}

int	Location::get_status(void) const
{
	return (this->status);
}

std::string	Location::get_body_size(void) const
{
	return (this->body_size);
}

void	Location::set_upload(std::string line)
{
	size_t	i;
	i = line.find(" ");
	this->upload_val = line.substr(i + 1, line.length());
	if (this->upload_val == "on")
		this->upload = true;
	//this->set_redirection(rf);
}

bool	Location::get_upload(void) const
{
	return (this->upload);
}

void	Location::set_autoindex(std::string line)
{
	size_t	i;
	i = line.find(" ");
	this->autoindex_val = line.substr(i + 1, line.length());
	if (this->autoindex_val == "on")
		this->autoindex = true;
	//this->set_upload(rf);
}

std::string	Location::get_autoindex(void) const
{
	return (this->autoindex_val);
}

void	Location::set_index(std::string line)
{
	size_t	start;
	start = line.find(" ");
	if (start == std::string::npos)
		throw (SyntaxError());
	this->index_val = line.substr(start + 1, line.length());
	//this->set_autoindex(rf);
}

std::string	Location::get_index(void) const
{
	return (this->index_val);
}

void	Location::set_root(std::ifstream &rf)
{
	std::string line;

	while (!rf.eof())
	{
		getline(rf, line);
		if (line == "\tlend")
			return ;
		if (line.compare(0, 6, "\t\troot") == 0)
			this->root_val = this->set_values(line);
		if (line.compare(0, 7, "\t\tindex") == 0)
			this->set_index(line);
		if (line.compare(0, 11, "\t\tautoindex") == 0)
			this->set_autoindex(line);
		if (line.compare(0, 8, "\t\tupload") == 0)
			this->set_upload(line);
		if (line.compare(0, 8, "\t\treturn") == 0)
			this->set_redirection(line);
		if (line.compare(0, 14, "\t\terror_pages:") == 0)
			this->set_error_pages (line);
		if (line.compare(0, 4, "\t\t\t/") == 0)
			this->set_error_path (line);
		if (line.compare(0, 6, "\t\tcgi:") == 0)
			this->set_cgi(line);
		if (line.compare(0, 5, "\t\t\t\t/") == 0)
			this->set_cgi_path(line);
	}
}

std::string	Location::get_root(void) const
{
	return (this->root_val);
}

void	Location::set_location(std::ifstream &rf)
{
	this->upload = false;
	this->autoindex = false;
	this->cgi = false;
	this->location_val = "";
	this->root_val = "";
	this->autoindex_val = "";
	this->upload_val = "";
	this->status_str = "";
	this->error_path = "";
	this->status = 301;
	std::string line;

	while (!rf.eof())
	{
		getline(rf, line);
		if (line.compare(0, 9, "\tlocation") == 0)
		{
			this->location_val = this->set_values(line);
			this->location_val = this->location_val.substr(0, this->location_val.length() - 1);
			this->set_root(rf);
			return ;
		}
	}
}

std::string	Location::get_location(void)const
{
	return (this->location_val);
}

Location::~Location(){}
