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
	std::string str(client.parse._data["path"]);
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


Response::Response(Client &client):client(client)
{
	this->readed = 0;
	this->content_length = std::atoi(client.parse._data["Content-Length"].c_str());
	this->is_done = false;
	path = "/Users/orbiay/Desktop/Webserv_v2/body2";
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

void Response::Get(Server &server) {
	// (void)server;
	std::string root = "." + client.parse._data["path"];
    std::string content_type = getContentType(server);
	std::ifstream infile(root.c_str());
	std::string header;
	std::cout<<root<<std::endl;
	if (!infile.good())
	{
		header = "HTTP/1.1 404 not found\nContent-Type: " + content_type + "\nContent-Length: 213r\r\nConnection: closed\r\n\r\n";
		server.write_in_socket_client(header,"404error.html", client);
	}
	else
	{
		infile.close();
		if (is_directory_or_file(root) == FILE)
		{
			header = "HTTP/1.1 200 OK\nContent-Type: " + content_type + "\nContent-Length: 392\r\nConnection: closed\r\n\r\n";
			server.write_in_socket_client(header,root,client);
		}
		else if (is_directory_or_file(root) == DIRE)
		{
			//check is auto index on
			server.default_index = "index.html";
			if (is_directory_or_file(root + server.default_index) != FILE)
			{
				
				std::cout<<"AAAAAAAAAAAAAAAA"<<std::endl;
				header = "HTTP/1.1 404 not found\nContent-Type:text/html\nContent-Length: 213\r\nConnection: closed\r\n\r\n";
				server.write_in_socket_client(header,"404error.html", client);
			}
			else
			{
				std::cout<<"IM HERE"<<std::endl;
				header = "HTTP/1.1 200 OK\nContent-Type:  text/html\nContent-Length: 506\r\nConnection: closed\r\n\r\n";
				server.write_in_socket_client(header,root + server.default_index,client);
			}
		}
	}
}


int Response::read_and_write(Client &client)
{
	int i = 0;
	
	while (client.position  + i  < content_length)
	{
		write(client.fd_file, &client.body[client.position + i],1);
		// printf("\n*");
		// write(1,&client.body[client.position + i],1);
		// printf("*\n");
		printf("\n|%c|\n", client.body[29384]);
		//std::cout<<client.position<<std::endl;
		if (i == 1024)
		{
			//i++;
			client.position += i;
			client.position++;
			std::cout<<"i1 = "<<i<<std::endl;
			return (i);
		}
		i++;
	}
	std::cout<<"i2 = "<<i<<std::endl;
	client.position += i;
	std::cout<<	"position = "<<client.position <<" content length =  "<<content_length <<std::endl;
	return(i);
}

void Response::Post(Server &server) {
	// (void)server;
	// std::string path = "/Users/fbouanan/Desktop/Webserv_v2/fouad.html";
	// int result;
	// result = chmod(path.c_str(), S_IRUSR | S_IWUSR);
	// client.parse._data["path"];
	// int content_length = std::stoi(client.parse._data["Content-Length"]);
	int upload = 1;
	//printf("str = %s\n",client->body.c_str());
	if (!client.enter)
	{
		client.fd_file = open(path.c_str(),O_CREAT | O_RDWR | O_TRUNC);
		client.enter = true;
	}
	if (upload) {
		int f = read_and_write(client);
		if (f < 1024) {
			client.is_finish = true;
			std::cout<<"f1 = "<<f<<std::endl;
			//std::cout<<"*************HOLA************"<<std::endl;
			//exit(1);
			server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: 215\r\n\r\n","201success.html",client);
		}
		else 
			std::cout<<"f2 = "<<f<<std::endl;
	}
	// else if (cgi) {

	// }
}

void Response::Delete(Server &server) {
	(void)server;
}

Response::~Response() {
	
}
