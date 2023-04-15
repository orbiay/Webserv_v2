/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:44:40 by fbouanan          #+#    #+#             */
/*   Updated: 2023/04/15 01:38:27 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http.hpp"
#include "CGI.hpp"

#include <string>

void Response::size_file(std::string file_name)
{
	std::ifstream file(file_name, std::ifstream::ate | std::ifstream::binary);
    if (file.is_open())
	{
        client.sizefile = to_string(file.tellg());
		file.close();
	}
    else {
        client.is_delete = true;
		file.close();
		//exit(0);
    }
}

int Response::is_directory_or_file(std::string path)
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
	std::string str(client.extension);
    size_t pos = str.find(".");
	if (pos == std::string::npos)
		return "application/octet-stream";
	std::string fileExtension = str.substr(pos);
	if (fileExtension == ".mp4")
		return "video/mp4";
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


Response::Response(Client &client):client(client)
{
	this->readed = 0;
	this->content_length = std::atoi(client.parse._data["Content-Length"].c_str());
	this->is_done = false;
	path = "body2";
	result = chmod(path.c_str(), S_IRUSR | S_IWUSR);
	is_exist.open(path);
	//outfile.open(path);
	//if (!outfile.is_open()) {
	//	perror("error");
	//}
}

Response::Response(const Response &r) :client(r.client) {
	*this = r;
}

Response Response::operator=(const Response &r) {
	this->client = r.client;
	return *this;
}

size_t	getFileSize(const std::string& name);
//{
//	std::ifstream file(name, std::ifstream::ate | std::ifstream::binary);
//	size_t size = 0;
//    if (file.is_open())
//	{
//       	size = file.tellg();
//		file.close();
//	}
//    else {
//		file.close();
//    }
//	return size;
//}

std::string size_t_to_string(size_t value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

void Response::Post(Server &server, int flag) {
	std::string path = this->client.location.root_val + this->client.location.location_val;
	//int upload = 1;
	// std::cout << "|" << server.server_config.L[0].root_val << "|" << std::endl;
	// std::cout << "|" << server.server_config.L[0].upload << "|" << std::endl;
	// exit(0);
	if (this->client.location.upload) {
		// std::cout << "upload" << std::endl;
			// printf("here\n");
		if (flag == FILE) {
			rename(client.file_name.c_str(), path.c_str());
			server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: 215\r\n\r\n","201success.html",client);
		}
		else if(flag == DIRE) {
			std::cout << "root_val = " << "|" << this->client.location.root_val << "|" << std :: endl;
			std::cout << "index_val = " << "|" << this->client.location.index_val << "|" << std :: endl;
			if (!this->client.location.index_val.empty()) {
				std::cout << "here 1" << std::endl;
				rename(client.file_name.c_str(), (this->client.location.root_val + this->client.location.index_val).c_str());
				server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: 215\r\n\r\n","201success.html",client);
			}
			else {
				server.write_in_socket_client("HTTP/1.1 403 Forbidden\nContent-Type: text/html\nContent-Length: 214\r\n\r\n","403forbidden.html",client);
			}
		}

	}
	else if (server.server_config.cgi)
	{
		CGI C;
		int	f;
		f = C.cgi(server.server_config, client, NULL);
		size_t rand_size = getFileSize("rand");
		std::string str = size_t_to_string(rand_size);
		server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: application/json\nContent-Length: " + str + "\r\n\r\n","rand",client);
		
	}
}

void Response::Delete(Server &server) {
	(void)server;

}

Response::~Response() {

}
