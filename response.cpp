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
	this->readed = 0;
	this->content_length = std::stoi(client.parse._data["Content-Length"]);
	this->is_done = false;
}

Response::Response(const Client &_client) {
	this->client = _client;
	this->readed = 0;
	this->content_length = std::stoi(client.parse._data["Content-Length"]);
	this->is_done = false;
	path = "/Users/fbouanan/Desktop/Webserv_v2/fouad.html";
	result = chmod(path.c_str(), S_IRUSR | S_IWUSR);
	is_exist.open(path);
	outfile.open(path);
	if (!outfile.is_open()) {
		perror("error");
	}

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

// bool is_directory(const std::string& path) {
//   std::filesystem::path p(path);
//   return std::filesystem::is_directory(p);
// }

void Response::Post(Server &server) {
			printf("aaaaaaaaaaaaaaa\n");
	// std::string path = "/Users/fbouanan/Desktop/Webserv_v2/fouad.html";
	// int result;
	// result = chmod(path.c_str(), S_IRUSR | S_IWUSR);
	// client.parse._data["path"];
	// int content_length = std::stoi(client.parse._data["Content-Length"]);
	int upload = 1;
	if (upload) {
		// if (is_directory(path)) {

		// }
		// std::ifstream is_exist(path);
		if (!is_exist.is_open() || this->is_done) {
			// std::ofstream outfile;
			// outfile.open(path);
			// if (!outfile.is_open()) {
			// 	perror("error");
			// }
			if (content_length <= 1024) {
				printf("here 1\n");
				outfile << client.body.substr(this->readed, content_length);
				outfile.close();
				server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: 215\r\n\r\n","201success.html", client);
			}
			else if (content_length > 1024) {
				printf("here 2\n");
				std::cout << this->readed << std::endl;
				outfile << client.body.substr(this->readed, 1024);
				this->is_done = true;
				content_length -= 1024;
				this->readed += 1024;
			}
			if (this->readed == content_length) {
				printf("here 3\n");
				outfile.close();
				this->is_done = false;
				server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: 215\r\n\r\n","201success.html", client);
			}
		}
		if (is_exist.is_open()) {
			printf("here 4\n");
			server.write_in_socket_client("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 186\r\n\r\n","200exists.html", client);
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
