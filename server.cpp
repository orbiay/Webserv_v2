/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 02:12:46 by fbouanan          #+#    #+#             */
/*   Updated: 2023/04/14 02:19:33 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"http.hpp"
Server::Server(){
	
}


Server::~Server(){

}

size_t is_carriage(std::string line, Client &client) {
	
	size_t pos = line.find("\r\n\r\n");
	if (pos == std::string::npos)
		return 0;
	else {
		client.readyToParse = true;
		return pos;
	}
}

bool	checkifchuncked(std::string request) {
	std::vector<std::string> output;
	std::string token;
	std::stringstream ss(request);
	while (std::getline(ss, token, '\n')) {
		output.push_back(token);
	}
	std::vector<std::string>::iterator it;
	for (it = output.begin(); it != output.end(); it++){
		std::string tmp = *it;
		if (tmp.find("Transfer-Encoding: chunked") != std::string::npos) {
			return true;
		}
	}
	return false;
}

void putstr(std::string str) {
	char *s = (char *)str.c_str();
	int i = 0;
	while (s[i]) {
		write(1, &s[i++], 1);
	}
	write (1, "\n", 1);
}

bool findHex(Client &client) {
	char *s;
	int len;

	if ((!memmem(client._hex, client.hex_len, "\r\n", 2)))
		return false;
	s = (char *)memmem(client._hex + 2, client.hex_len, "\r\n", 2);
	if (!s)
		return false;
	len = s - (client._hex + 2);
	memcpy(client.hex_c, client._hex + 2, len);
	memset(client._hex, 0, 20);
	memcpy(client._hex, client.hex_c, len);
	client.hex_ready = true;
	return (true);
}

void handel_chunked(Client &client, char *_body, int i) {
	int reades = 0;
	client.hex_ready = false;
	while (reades < i) {
		if (!client.chunk_size) {
			while (reades < i) {
				client._hex[client.hex_len++] = _body[reades++];
				if (findHex(client))
					break;
			}
			if (!client.hex_ready)
				break;
			client.chunk_size = std::strtoul(client._hex, nullptr, 16);
			client.hex_len = 0;
			memset(client._hex, 0, 20);
			if (!client.chunk_size) {
				close(client.file);
				client.bodyReady = true;
				client.ready = true;
				break;
			}
		}
		while (reades < i && client.chunk_size) {
			write(client.file ,_body + reades, 1);
			client.chunk_size--;
			reades++;
		}
	}
}

size_t	getFileSize(const std::string& name)
{
	std::ifstream file(name, std::ifstream::ate | std::ifstream::binary);
	size_t size = 0;
    if (file.is_open())
	{
       	size = file.tellg();
		file.close();
	}
    else {
		file.close();
    }
	return size;
}

char* substr_no_null(const char* str, int start, int length, int str_len) {
     if (start >= str_len) {
        return NULL;
    }
    if (start + length > str_len) {
        length = str_len - start;
    }
    char* substr = new char[length + 1];
    if (substr == NULL) {
        return NULL;
    }
    const char* src = str + start;
    char* dest = substr;
    while (length-- > 0) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return substr;
}

void Server::read_from_socket_client(Client &client)
{
	char line[10240];
	memset(line,'\0', 10240);
	int i  = recv(client.fd_client, line, 10240, 0);

	// if request doesn't exist chenge is_delete variable to true for drop it.
	if (!client.alrChecked) {
		client.ret = is_carriage(std::string(line), client);
		if (client.readyToParse) {
			client.header = std::string(line).substr(0, client.ret);
			// std::cout << "header = " << client.header.length() << std::endl;
			client.parse.parse_request(client.header);
			// std::cout << "content = " << client.parse._data["Content-Length"] << std::endl;
			client.b_pos = client.ret + 4;
			client.isChuncked = checkifchuncked(client.header);
			client.j = 1;
			client.alrChecked = true;
		}
		else{
			client.is_delete = true;
        	close(client.fd_client);
			FD_CLR(client.fd_client,&current);
			return;
		}
			
	}
	if (!client.isChuncked) {
		if (client.j) {
			char *holder;
			holder = substr_no_null(line, client.b_pos, i, i);
			std::cout <<  (size_t)std::atoi(client.parse._data["Content-Length"].c_str()) << std::endl;
			if (getFileSize(client.file_name) < (size_t)std::atoi(client.parse._data["Content-Length"].c_str())) {
				write(client.file, holder, i - client.b_pos);
				if (getFileSize(client.file_name) == (size_t)std::atoi(client.parse._data["Content-Length"].c_str())) {
					close(client.file);
					client.bodyReady = true;
					client.ready = true;
				}
			}
			else {
				close(client.file);
				client.bodyReady = true;
				client.ready = true;
			}
			client.j = 0;
		}
		else {
			if (getFileSize(client.file_name) < (size_t)std::atoi(client.parse._data["Content-Length"].c_str())) {
				write(client.file, line, i);
				if (getFileSize(client.file_name) == (size_t)std::atoi(client.parse._data["Content-Length"].c_str())) {
					close(client.file);
					client.bodyReady = true;
					client.ready = true;
				}
			}
			// else {
			// 	close(client.file);
			// 	client.bodyReady = true;
			// 	client.ready = true;
			// }
		}
	}
	else if (client.isChuncked) {
		if (client.j) {
			client.b_pos -=2;
			char *holder;
			holder = substr_no_null(line, client.b_pos, i, i);
			handel_chunked(client, holder, i - client.b_pos);
			delete(holder);
			client.j = 0;
		}
		else {
			handel_chunked(client, line, i);
		}
	}
}

void Server::write_in_socket_client(std::string str, std::string file , Client &client)
{
	std::cout<<"write in client = "<<client.fd_client<<std::endl;
	char *s;
	s = new char[1024];
    memset(s, '\0', 1024);
    int i = str.length();
    if (client.start_writting == 1)
    {
	    client.fd_file = open (file.c_str(),O_RDONLY);
        if (client.fd_file == -1){
			close(client.fd_client);
			FD_CLR(client.fd_client,&current);
            client.is_delete = true;
        }
        client.start_writting = 0;
		write(client.fd_client,str.c_str(),strnlen(str.c_str(),1023));
		return ;
    }
    else if (client.start_writting == 0)
    {
        i = read(client.fd_file,s,1023);
    }
    // write(1,"\n",1);
	int b = send(client.fd_client,s,i,0);
	std::cout << " send = "<< b << std::endl;
	if (b == 0)
		usleep(1);
	client.read_size += b;
	//std::cout<<"->>>>>>>>"<<client.read_size<<std::endl;
    if (b < 1023)
    {
        client.is_delete = true;
		//std::cout << "Error : " << strerror(errno) << std::endl;
		close(client.fd_file);
        close(client.fd_client);
		FD_CLR(client.fd_client,&current);
		delete(s);
        return;
    }
    if (i < 1023)
    {
        client.is_delete = true;
		close(client.fd_file);
        close(client.fd_client);
		FD_CLR(client.fd_client,&current);
        return;
    }
   	delete(s);
}


fd_set Server::initializer()
{
	FD_ZERO(&current);
	return (current);
}