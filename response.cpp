/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:44:40 by fbouanan          #+#    #+#             */
/*   Updated: 2023/04/14 04:26:20 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http.hpp"

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

// void Response::Get(Server &server) {
// 	// (void)server;
// 	std::string root = "." + client.parse._data["path"];
//     std::string content_type = getContentType(server);
// 	std::ifstream infile(root.c_str());
// 	std::string header;
// 	// std::cout<<root<<std::endl;
// 	std::string auto_index = "on";
// 	if (!infile.good())
// 	{
// 		header = "HTTP/1.1 404 not found\nContent-Type: " + content_type + "\nContent-Length: 213r\r\nConnection: closed\r\n\r\n";
// 		server.write_in_socket_client(header,"404error.html", client);
// 	}
// 	else
// 	{
// 		infile.close();
// 		if (is_directory_or_file(root) == FILE)
// 		{
// 			header = "HTTP/1.1 200 OK\nContent-Type: " + content_type + "\nContent-Length: 392\r\nConnection: closed\r\n\r\n";
// 			server.write_in_socket_client(header,root,client);
// 		}
// 		else if (is_directory_or_file(root) == DIRE)
// 		{
// 			if (auto_index == "on")
// 			{
// 				server.default_index = "index.html";
// 				if (is_directory_or_file(root + server.default_index) != FILE)
// 				{

// 					// std::cout<<"AAAAAAAAAAAAAAAA"<<std::endl;
// 					header = "HTTP/1.1 404 not found\nContent-Type:text/html\nContent-Length: 	213\r\nConnection: closed\r\n\r\n";
// 					server.write_in_socket_client(header,"404error.html", client);
// 				}
// 				else
// 				{
// 					// std::cout<<"IM HERE"<<std::endl;
// 					header = "HTTP/1.1 200 OK\nContent-Type:  text/html\nContent-Length: 506\r\nConnection: 	closed\r\n\r\n";
// 					server.write_in_socket_client(header,root + server.default_index,client);
// 				}
// 			}
// 			else
// 			{
// 				header = "HTTP/1.1 403 Forbidden\nContent-Type:text/html\nContent-Length: 	169\r\nConnection: closed\r\n\r\n";
// 				server.write_in_socket_client(header,"403error.html", client);
// 			}
// 		}
// 	}
// }


int Response::read_and_write(Client &client)
{
	std::cout <<client.request;
	// client.file = hna fih lbody li ja mn request;
	// client.fd_file = hna fin khas ytktb dak l body;
	// char* buffer = new char[1024];
	//close(client.file);
	//close(client.fd_file);
	//client.fd_file = open ("body2",O_CREAT | O_RDWR | O_APPEND);
	//client.file = open (client.file_name.c_str(),O_CREAT | O_RDWR | O_APPEND);
	// int i = 1;
    //while (i)
    //{
		// printf("here\n");
		// i = read(client.file, buffer, 1024);
		// if (i < 0)
		// 	exit(0);
		// std::cout<<"file  = "<<client.file<< " fd_file = " << client.fd_file<<std::endl;
		// std::cout<<buffer<<std::endl;
		// write(client.post_fd,buffer,i);
    //}
	return (0);
	// int i = 0;
	// while (client.position  + i  < content_length)
	// {
	// 	write(client.fd_file, &client.body[client.position + i],1);
	// 	// printf("\n*");
	// 	// write(1,&client.body[client.position + i],1);
	// 	// printf("*\n");
	// 	//std::cout<<client.position<<std::endl;
	// 	if (i == 1024)
	// 	{
	// 		//i++;
	// 		client.position += i;
	// 		client.position++;
	// 		std::cout<<"i1 = "<<i<<std::endl;
	// 		return (i);
	// 	}
	// 	i++;
	// }
	// std::cout<<"i2 = "<<i<<std::endl;
	// client.position += i;
	// std::cout<<	"position = "<<client.position <<" content length =  "<<content_length <<std::endl;
	// return(i);
	// int i = 1;
	
	// while (i)
	// {
	// 	char c;
	// 	i += read(client.file, &c,1);
	// 	std::cout<<"c =  "<<c<<std::endl;
	// 	write(1, &c,1);
	// 	if (i == 10)
	// 		exit(0);
	// 		// std::cout<<"i1 = "<<i<<std::endl;
	// }
	// // std::cout<<"i2 = "<<i<<std::endl;
	// // std::cout<<	"position = "<<client.position <<" content length =  "<<content_length <<std::endl;
	// return(i);
}

// int	is_file(Client &client) {
// 	std::string s = "./index.html";
	
// }

void Response::Post(Server &server, int flag) {
	// std::string location = "/home";
	// std::string index = "./index.html";
	//int upload = 1;
	// std::cout << "|" << server.server_config.L[0].root_val << "|" << std::endl;
	// std::cout << "|" << server.server_config.L[0].upload << "|" << std::endl;
	// exit(0);
	// std::cout << "index_val = " << "|" << this->client.location.index_val << "|" << std :: endl;
	if (this->client.location.upload) {
		// std::cout << "upload" << std::endl;
			// printf("here\n");
		if (flag == FILE) {
			rename(client.file_name.c_str(), "data/FILE_video.mp4");
				server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: 215\r\n\r\n","201success.html",client);
			// }
		}
		else if(flag == DIRE) {
			if (this->client.location.index_val.empty()) {
				// std::cout << "index_val = " << "|" << this->client.location.index_val << "|" << std :: endl;
				rename(client.file_name.c_str(), "data/DIR_video.mp4");
				server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: 215\r\n\r\n","201success.html",client);

			}
			else {
				server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: 214\r\n\r\n","403forbidden.html",client);
			}
		}

	}
	// else if (server.server_config.cgi) {
	// 	cgi(server.server_config);
	// }
}

void Response::Delete(Server &server) {
	(void)server;

}

Response::~Response() {

}
