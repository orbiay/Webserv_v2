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

#include <string>

int is_directory_or_file(std::string path)
{
	struct stat status;
	if (stat(path.c_str(), &status) != 0) {
        std::cerr << "Error getting file/directory informaion\n";
        return 1;
    }
	if (S_ISDIR(status.st_mode)) {
       return (DIRE);
    }
	else if (S_ISREG(status.st_mode)) {
        return (FILE);
    }
	else {
        return (-1);
    }
}

std::string Response::getContentType(Server &server) {

	(void)server;
	std::string str(client->parse._data["path"]);
    size_t pos = str.find(".");
	if (pos == std::string::npos)
		return "application/octet-stream";
	std::string fileExtension = str.substr(pos);
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


Response::Response(Client *client) 
{
	this->readed = 0;
	this->content_length = std::atoi(client->parse._data["Content-Length"].c_str());
	this->is_done = false;
	path = "/Users/orbiay/Desktop/Webserv_v2/fouad.html";
	result = chmod(path.c_str(), S_IRUSR | S_IWUSR);
	is_exist.open(path);
	outfile.open(path);
	if (!outfile.is_open()) {
		perror("error");
	}
	this->client = client;
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
	std::string root = "." + client->parse._data["path"];
    std::string content_type = getContentType(server);
	std::ifstream infile(root.c_str());
	std::string header;
	std::cout<<root<<std::endl;
	if (!infile.good())
	{
		header = "HTTP/1.1 404 not found\nContent-Type: " + content_type + "\nContent-Length: 213\r\n\r\n";
		server.write_in_socket_client(header,"404error.html", *client);
	}
	else
	{
		infile.close();
		header = "HTTP/1.1 200 OK\nContent-Type: " + content_type + "\nContent-Length: 587\r\nConnection: closed\r\n\r\n";
		server.write_in_socket_client(header,root,*client);
	}
}


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
		// if (!is_exist.is_open() || this->is_done) {
			// std::ofstream outfile;
			// outfile.open(path);
			// if (!outfile.is_open()) {
			// 	perror("error");
			// }
			if (content_length <= 1024) {
				printf("here 1\n");
				outfile << client->body.substr(this->readed, content_length);
				outfile.close();
				Http::finish = true;
				server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: 215\r\n\r\n","201success.html", *client);
			}
			else if (content_length > 1024) {
				printf("here 2\n");
				std::cout << this->readed << std::endl;
				outfile << client->body.substr(this->readed, 1024);
				this->is_done = true;
				content_length -= 1024;
				this->readed += 1024;
			}
			if (this->readed == content_length) {
				printf("here 3\n");
				outfile.close();
				this->is_done = false;
				Http::finish = true;
				std::cout << Http::finish << std::endl;
				server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: 215\r\n\r\n","201success.html", *client);
			}
		// }
		// if (is_exist.is_open()) {
		// 	printf("here 4\n");
		// 	server.write_in_socket_client("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 186\r\n\r\n","200exists.html", client);
		// }
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
