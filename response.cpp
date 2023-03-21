/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:44:40 by fbouanan          #+#    #+#             */
/*   Updated: 2023/03/17 18:35:44 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http.hpp"
#include <sys/stat.h>

Response::Response() {
	
}

Response::Response(const Client &_client) {
	this->client = _client; 
}

Response::Response(const Response &r) {
	*this = r;
}

Response Response::operator=(const Response &r) {
	this->client = r.client;
	return *this;
}

void Response::Get(Server &server) {
	(void)server;
}

void Response::Post(Server &server) {
	std::string path = "/Users/fbouanan/Desktop/Webserv_v2/fouad.html";
	int result;
	result = chmod(path.c_str(), S_IRUSR | S_IWUSR);
	// client.parse._data["path"];
	int upload = 1;
	if (upload) {
		std::ifstream is_exist(path);
		if (!is_exist) {
			std::ofstream outfile;
			outfile.open(path);
			if (!outfile.is_open()) {
				perror("error");
			}
			outfile << client.body;
			outfile.close();
			server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: 215\r\n\r\n","201success.html", client);
		}
		if (is_exist) {
			server.write_in_socket_client("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 152\r\n\r\n","fouad.html", client);
		}
		// std::cout << "--------___--------------body--------------------\n";
		// std::cout << client.body << std::endl;
		// std::cout << "--------------------------------------------\n";
		
	}
	// else if (cgi) {

	// }
}

void Response::Delete(Server &server) {
	(void)server;
}

Response::~Response() {
	
}
