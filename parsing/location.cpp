/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomman <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:20:30 by aomman            #+#    #+#             */
/*   Updated: 2023/03/16 17:20:32 by aomman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"location.hpp"

Location::Location()
{
}

const char	*Location::NotOpen::what() const throw()
{
	return ("file not found");
}

const char	*Location::EndNotReached::what() const throw()
{
	return ("you must set end of confige file");
}

const char	*Location::Nofile::what() const throw()
{
	return ("server rquire config file");
}

const char	*Location::YmlFileError::what() const throw()
{
	return ("configuration file must be .yml");
}

const char *Location::PathError::what() const throw()
{
	return ("invalid path");
}

const char *Location::SyntaxError::what() const throw()
{
	return ("Syntax Error");
}

std::string	Location::set_values(std::string line)
{
	size_t	start;
	start = line.find("/");
	if (start == std::string::npos)
		throw(PathError());
	this->line_val = line.substr(start, line.length());
	return (this->line_val);
}

void	Location::set_config_items()
{
	if (this->location_val == "")
		throw (SyntaxError());
	if (this->root_val == "")
		throw (SyntaxError());
	if (this->index_val == "")
		throw (SyntaxError());
	if (this->upload_val == "" || (this->upload_val != "on" && this->upload_val != "off"))
		throw (SyntaxError());
	this->config_items.insert(std::make_pair("location", this->location_val));
	this->config_items.insert(std::make_pair("root", this->root_val));
	this->config_items.insert(std::make_pair("index", this->index_val));
	this->config_items.insert(std::make_pair("upload", this->upload_val));
}

std::map<std::string, std::string>	Location::get_config_item(void) const
{
	return (this->config_items);
}

void	Location::set_upload(std::ifstream &rf)
{
	std::string line;
	size_t	i;

	while (!rf.eof())
	{
		getline(rf, line);
		if (line.compare(0, 8, "\t\tupload") == 0)
		{
			i = line.find(" ");
			this->upload_val = line.substr(i + 1, line.length());
			return ;
		}
	}
}

std::string	Location::get_upload(void) const
{
	return (this->upload_val);
}

void	Location::set_index(std::ifstream &rf)
{
	std::string	line;
	size_t	start;
	while (!rf.eof())
	{
		getline(rf, line);
		if (line.compare(0, 7, "\t\tindex") == 0)
		{
			start = line.find(" ");
			this->index_val = line.substr(start + 1, line.length());
			this->set_upload(rf);
			return ;
		}
	}
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
		if (line.compare(0, 6, "\t\troot") == 0)
		{
			this->root_val = this->set_values(line);
			this->set_index(rf);
			return ;
		}
	}
}

std::string	Location::get_root(void) const
{
	return (this->root_val);
}

void	Location::set_location(std::ifstream &rf)
{
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

void	Location::check_serverfile(std::ifstream &rf)
{
	std::string line;
	
	while (!rf.eof())
	{
		getline(rf, line);
		if (line == "server:")
			this->set_location(rf);
	}
}

void	Location::check_yml(char *str)
{
	size_t i;
	this->file_name = (std::string)str;
	std::string	yml;
	yml = ".yml";
	i = this->file_name.find(yml, 0);
	if (i == std::string::npos)
		throw(YmlFileError());
}

std::string		Location::getData(void) const
{
	return (this->file_name);
}

Location::~Location(){}
