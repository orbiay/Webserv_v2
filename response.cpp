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

#include <string>

std::string getContentType(const std::string& fileExtension) {
    if (fileExtension == ".html" || fileExtension == ".htm") {
        return "text/html";
    } else if (fileExtension == ".css") {
        return "text/css";
    } else if (fileExtension == ".js") {
        return "application/javascript";
    } else if (fileExtension == ".json") {
        return "application/json";
    } else if (fileExtension == ".png") {
        return "image/png";
    } else if (fileExtension == ".jpg" || fileExtension == ".jpeg") {
        return "image/jpeg";
    } else if (fileExtension == ".gif") {
        return "image/gif";
    } else if (fileExtension == ".svg") {
        return "image/svg+xml";
    } else {
        return "application/octet-stream";
    }
}


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
	// (void)server;
	std::string root = "." + client.parse._data["path"];
	std::string str(client.parse._data["path"]);
    size_t pos = str.find(".");
    std::string content_type = getContentType(str.substr(pos));
	std::ifstream infile(root.c_str());
	if (!infile.good())
	{
		std::string header;
		header = "HTTP/1.1 404 not found\nContent-Type: " + content_type + "\nContent-Length: 213\r\n\r\n";
		server.write_in_socket_client(header,"404error.html", client);
	}
	//else{
	//	
	//	if (
//
	//	)
	//}

}

void Response::Post(Server &server) {
	std::string path = "/Users/orbiay/Desktop/Webserv_v2/fouad.html";
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
