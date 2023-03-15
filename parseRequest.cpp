/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:39:32 by fbouanan          #+#    #+#             */
/*   Updated: 2023/03/14 20:10:21 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http.hpp"


parseRequest::parseRequest() {
	
}

parseRequest::parseRequest(const parseRequest &data)
{
	*this = data;
}

parseRequest::~parseRequest() {

}

parseRequest &parseRequest::operator=(const parseRequest &data) 
{
	this->_data = data._data;
	return *this;
}


void	parseRequest::parse_url(std::string _url)
{
	std::string token;
	std::stringstream ss(_url);
	while (std::getline(ss, token, ' ')) {
		if (token == "GET" || token == "POST" || token == "DELETE") {
			this->_data["method"] = token;
			// this->_data.insert(std::make_pair("method", token));
		}
		else if (token[0] == '/') {
			// this->_data.insert(std::make_pair("path", token));
			this->_data["path"] = token;
		}
		else {
			// this->_data.insert(std::make_pair("version", token));
			this->_data["version"] = token;
		}
	}
}

void	parseRequest::parse_infos(std::string _data)
{
	std::vector<std::string> output;
	std::string token;
	std::stringstream ss(_data);
	while (std::getline(ss, token, ' ')) {
		output.push_back(token);
	}
	if (output[0] == "Host:"){
		// this->_data["Host"] = output[1];
		this->_data.insert(std::make_pair("Host", output[1]));
	}
	else if (output[0] == "Content-Type:") {
		this->_data.insert(std::make_pair("Content-Type", output[1]));
	}
	else if (output[0] == "Content-Length:") {
		this->_data.insert(std::make_pair("Content-Length", output[1]));
	}
}

void    parseRequest::parse_request(std::string request)
{
	std::cout << "----------------------------------------------------" << std::endl;
	std::vector<std::string> output;
	std::string token;
	std::stringstream ss(request);
	while (std::getline(ss, token, '\n')){
		output.push_back(token);
	}

	parse_url(output[0]);
	std::vector<std::string>::iterator it;
	for (it = output.begin() + 1; it != output.end(); it++){
		parse_infos(*it);
	}

	std::cout << "----------------------------------------------------" << std::endl;
}

int	check_url(std::string url)
{
	std::cout << "url = " << url << std::endl;
	std::string::iterator it = url.begin();
	while (it != url.end()) {
		if (!isprint(*it))
		{
			return (1);
		}
		it++;
	}
	return (0);
}

int check_url_size (std::string url)
{
	if (url.size() > 2048)
		return (1);
	return (0);
}

void parseRequest::display_request(parseRequest parse)
{
	std::map<std::string, std::string>::iterator it = parse._data.begin();
					// showning results by iterating inside map container
		while (it != parse._data.end())
 		{
 		  std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
 		  ++it;
 		}
}

void	parseRequest::check_request(Server server, const Client &iter) {
		
	if (this->_data["method"] == "POST") {
		printf("heer\n");
		if (this->_data["Content-Length"].length() == 1){
			printf("here\n");
			server.write_in_socket_client("HTTP/1.1 400 KO\nContent-Type: text/html\nContent-Length: 203\r\n\r\n","400error.html", iter);
		}
	}
	else if (check_url(this->_data["path"])) {
		server.write_in_socket_client("HTTP/1.1 400 KO\nContent-Type: text/html\nContent-Length: 203\r\n\r\n","400error.html", iter);
	}
	else if (check_url_size(this->_data["path"])) {
		server.write_in_socket_client("HTTP/1.1 414 KO\nContent-Type: text/html\nContent-Length: 220\r\n\r\n","414error.html", iter);
	}
	// request body larger then client max body size in config file
	
	

}


std::map<std::string, std::string> parseRequest::getData()
{
	return this->_data;
}