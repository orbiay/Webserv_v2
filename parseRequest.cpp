/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:39:32 by fbouanan          #+#    #+#             */
/*   Updated: 2023/03/18 18:01:33 by fbouanan         ###   ########.fr       */
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

void	parseRequest::save_body(std::string req) {

			printf("                 herrr\n");
	std::string token;
	std::stringstream ss(req);
	std::vector<std::string> tmp;
	while (std::getline(ss, token)) {
		tmp.push_back(token);
	}
	std::vector<std::string>::iterator it = tmp.begin();
	while (it != tmp.end()) {
		if (*it == "\n") {
			break;	
		}
		it++;
	}
	while (it != tmp.end()) {
		this->_body.push_back(*it);
		it++;
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
		//--------------------------------checking request-------------------------------------------
int	check_url(std::string url)
{
	std::string::iterator it = url.begin();
	while (it != url.end()) {
		if (!isprint(*it)){
			return (1);
		}
		it++;
	}
	return (0);
}

int check_url_size (std::string url) {
	if (url.size() > 2048)
		return (1);
	return (0);
}

int	matched_location(std::string url)
{
	t_hcode g_v;
	g_v.location = "/example";
	g_v.root = "/var/www/html";


	// std::cout << "pos = " << url.find(g_v.location) << std::endl;
	std::size_t pos = url.find(g_v.location);

	if (pos == 0) {
		std::string tmp = url.substr(g_v.location.length(), url.length());
		g_v.root.insert(g_v.root.length(), tmp);
		if (access(g_v.root.c_str(), R_OK) == -1) {
			return (1);
		}
		else
			return 0;
		std::cout << "root = " << g_v.root << std::endl;
		
	}
	
	// if (pos == std::string::npos) {
	// 	std::cout << "invalid url" << std::endl;
	// 	return (1);
	// }
	return (1);
}
		//-------------------------------------------------------------------------------------------


		//--------------------------------checking methods-------------------------------------------
void	check_methods(Server &server, Client &client)
{
	//Response res(client);
	// res.client = client.parse;
	if (client.parse._data["method"] == "GET") {
		// GET();
		std::cout << "----------------RAHA KHEDAMA A Z---------------------" << std::endl;
		//std::cout << res.client.parse._data["method"] << std::endl;
		std::cout << "----------------RAHA  MaKHEDAMA A Z---------------------" << std::endl;
	}
	else if (client.parse._data["method"] == "POST") {
		// POST();
		// this->res.Post(server, client, *this);
		// std::vector<std::string>::iterator it = this->_body.begin();
		std::cout << "----------------------body--------------------\n";
		std::cout << client.body << std::endl;
		std::cout << "--------------------------------------------\n";
	}

	else if (client.parse._data["method"] == "DELETE") {
		// DELETE();
	}
	else {
		server.write_in_socket_client("HTTP/1.1 405 KO\nContent-Type: text/html\nContent-Length: 221\r\n\r\n","405error.html", client);
	}
}

		//-------------------------------------------------------------------------------------------
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

void	parseRequest::check_request(Server &server,Client &iter) {
		
	if (this->_data["method"] == "POST") {
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
		//---------------------------------this part need confg file------------------------------------>
	// request body larger then client max body size in config file
	// else if (matched_location(this->_data["path"])) {
    // 	server.write_in_socket_client("HTTP/1.1 404 KO\nContent-Type: text/html\nContent-Length: 214\r\n\r\n","404error.html", iter);
	// }
		//---------------------------------------------------------------------------------------------->
	check_methods(server, iter);
}


std::map<std::string, std::string> parseRequest::getData()
{
	return this->_data;
}
