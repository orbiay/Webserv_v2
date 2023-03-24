#include"config.hpp"

Config::Config()
{
	this->upload = false;
}

void	Config::set_loc_conf()
{
	this->host = std::atoi(this->l.get_host().c_str());
	this->port = std::atoi(this->l.get_port().c_str());
	if (this->l.get_upload() == "on")
		this->upload = true;
	this->root = this->l.get_root();
	this->index = this->l.get_index();
	this->location = this->l.get_location();
}

int	Config::get_host() const
{
	return (this->host);
}

int	Config::get_port() const
{
	return (this->port);
}

bool	Config::get_upload() const
{
	return (this->upload);
}

std::string	Config::get_root() const
{
	return (this->root);
}

std::string	Config::get_index() const
{
	return (this->index);
}

std::string	Config::get_location() const
{
	return (this->location);
}

Config::~Config(){}
