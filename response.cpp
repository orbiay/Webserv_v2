/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:44:40 by fbouanan          #+#    #+#             */
/*   Updated: 2023/04/17 02:14:53 by fbouanan         ###   ########.fr       */
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
	//is_exist.open(path);
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
	int i = 0;
	if (this->client.location.upload) {
		// std::cout << "upload" << std::endl;
			// printf("here\n");
		if (flag == FILE) {
			rename(client.file_name.c_str(), path.c_str());
			server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: "+std::to_string(getFileSize(getErrorFileName(client,"201")))+"\r\n\r\n",getErrorFileName(this->client, "201"),client);
		}
		else if(flag == DIRE) {
			std::cout << "root_val = " << "|" << this->client.location.root_val << "|" << std :: endl;
			std::cout << "index_val = " << "|" << this->client.location.index_val << "|" << std :: endl;
			if (!this->client.location.index_val.empty()) {
				// std::cout << "here 1" << std::endl;
				rename(client.file_name.c_str(), (this->client.location.root_val + this->client.location.index_val).c_str());
				server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: "+std::to_string(getFileSize(getErrorFileName(client,"201")))+"\r\n\r\n",getErrorFileName(this->client, "201"),client);
			}
			else {
				server.write_in_socket_client("HTTP/1.1 403 Forbidden\nContent-Type: text/html\nContent-Length: "+std::to_string(getFileSize(getErrorFileName(client,"403")))+"\r\n\r\n",getErrorFileName(this->client, "403"),client);
			}
		}

	}
	else if (client.location.cgi)
	{
		CGI c;
		c.cgi(server.server_config, client, NULL);
		if(client.in_cgi == 0)
		{
			client.fd_rand = open("./rand",O_RDONLY);
			client.fd_rand_body = open("./randbody", O_CREAT | O_TRUNC | O_RDWR);
			size_file("./rand");
			int len = std::atoi(client.sizefile.c_str());
			char *s = new char[len + 1];
			memset(s,0,len + 1);
			int sizereaded = read(client.fd_rand,s,len);
			if (sizereaded)
			{
				std::string str(s);
				size_t pos = str.find("\r\n\r\n");
				if (pos != std::string::npos)
				{
					std::string body = str.substr(pos + 4);
					client.header ="HTTP/1.1 200 OK\r\nContent-Length:" + std::to_string(body.length()) +  "\r\n"+ str.substr(0, pos) + "\r\nConnection: closed\r\n\r\n";
					write(client.fd_rand_body,body.c_str(),body.length());
					close(client.fd_rand);
					close(client.fd_rand_body);
					delete [] s;
				}
				else 
				{
					close(client.fd_rand);
					close(client.fd_rand_body);
					delete [] s;
					close(client.fd_client);
					FD_CLR(client.fd_client,&Server::current);
					client.is_delete = true;
				}
			}
			else {
				close(client.fd_rand);
				close(client.fd_rand_body);
				delete [] s;
				close(client.fd_client);
				FD_CLR(client.fd_client,&Server::current);
				client.is_delete = true;
			}
			client.in_cgi = 1;
			return ;
		}
		std::cout << "i = " <<  i++ << std::endl;
		server.write_in_socket_client(client.header,"./randbody",client);
		return ;
	}
}

int delete_directory_contents(const std::string& dir_path) {
    DIR* dir = opendir(dir_path.c_str());
    if (!dir) {
        std::cerr << "Error opening directory " << dir_path << std::endl;
        return 1;
    }

    dirent* entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        std::string entry_path = dir_path + "/" + entry->d_name;
        if (entry->d_type == DT_DIR) {
            delete_directory_contents(entry_path);
            rmdir(entry_path.c_str());
        } else {
            unlink(entry_path.c_str());
        }
    }
    closedir(dir);
	return 0;
}

void Response::Delete(Server &server, int flag) {
	std::string path = this->client.location.root_val + this->client.location.location_val;
	std::cout << "path = " << path << std::endl;
	if (flag == FILE) {
		int file_to_delete = open(path.c_str(),0);
		if (file_to_delete < 0) {
			server.write_in_socket_client("HTTP/1.1 404 Not Found\nContent-Type: text/html\nContent-Length: "+std::to_string(getFileSize(getErrorFileName(client,"404")))+"\r\n\r\n",getErrorFileName(this->client, "404"),client);
		}
		if (remove(path.c_str()) == 0) {
			server.write_in_socket_client("HTTP/1.1 204 No Content\nContent-Type: text/html\nContent-Length: "+std::to_string(getFileSize(getErrorFileName(client,"204")))+"\r\n\r\n",getErrorFileName(this->client, "204"),client);
		}
	}
	else if (flag == DIRE) {
		if (path.rfind("/") == path.size() - 1) {
			if(delete_directory_contents(path))
				server.write_in_socket_client("HTTP/1.1 500 No Content\nContent-Type: text/html\nContent-Length: "+std::to_string(getFileSize(getErrorFileName(client,"500")))+"\r\n\r\n",getErrorFileName(this->client, "500"),client);
			else
				server.write_in_socket_client("HTTP/1.1 204 No Content\nContent-Type: text/html\nContent-Length: "+std::to_string(getFileSize(getErrorFileName(client,"204")))+"\r\n\r\n",getErrorFileName(this->client, "204"),client);
		}
		else {
			server.write_in_socket_client("HTTP/1.1 409 Conflict\nContent-Type: text/html\nContent-Length: "+std::to_string(getFileSize(getErrorFileName(client,"409")))+"\r\n\r\n",getErrorFileName(this->client, "409"),client);
		}
	}
}

Response::~Response() {

}
