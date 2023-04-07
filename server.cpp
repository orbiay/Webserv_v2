
#include"http.hpp"
Server::Server(){
	
}


Server::~Server(){

}

size_t is_carriage(std::string line) {
	
	size_t pos = line.find("\r\n\r\n");
	if (pos == std::string::npos)
		return 0;
	else 
		return pos;
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

void handel_chunked(Client &client, std::string _bodyy, int i) {
	int reades = 0;;
	client._body = (char *)_bodyy.c_str();
	std::string *n_hex = new std::string();
	client._hex = (char *)n_hex->c_str();
	client.hex_ready = false;
	while (reades < i) {
		if (!client.chunk_size) {
			while (reades < i) {
				// printf("here\n");
				client._hex[client.hex_len++] = client._body[reades++];
				if (findHex(client))
					break;
			}
			if (!client.hex_ready)
				break;
				std::cout << client._hex << std::endl;
			client.chunk_size =  std::strtoul(client._hex, nullptr, 16);;
			client.hex_len = 0;
			if (!client.chunk_size) {
				close(client.file);
				client.bodyReady = true;
				break;
			}
		}
		while (reades < i && client.chunk_size) {
			write(client.file ,client._body + reades, 1);
			client.chunk_size--;
			reades++;
		}
	}
	delete(n_hex);

	

	// std::string::iterator it = _body.begin();
	// size_t i;
	// size_t j;
	// if (i = _body.find("\r\n") && j == )
	// if (!client.h) {
	// 	client.crlf_pos = _body.find("\r\n");
	// 	client._hex = _body.substr(client.hex_pos, client.crlf_pos);
	// 	// client.h = 1;
	// }
	// std::cout << "crlf_pos = " << client.crlf_pos << std::endl;
	// std::cout << "hex_pos = " << client.hex_pos << std::endl;
	// std::cout << "|"<< client._hex << "|" <<  std::endl;
	// client.chunk_size = std::stoi(client._hex, nullptr, 16);
	// // client.content_length = 0;
	// client.crlf_pos += 2;
	// if (client.chunk_size > 0) {
	// 	client.next_crlf_pos = _body.find("\r\n", client.crlf_pos);
	// 	client.content = _body.substr(client.crlf_pos, client.next_crlf_pos - client.crlf_pos);
	// 	if (client.flag) {
	// 		client.hex_pos = _body.find("\r\n", client.next_crlf_pos) + 2;
	// 		client.crlf_pos = _body.find("\r\n", client.next_crlf_pos + 2);
	// 		if (client.hex_pos != std::string::npos && client.crlf_pos != std::string::npos) {
	// 			client._hex = _body.substr(client.hex_pos, client.crlf_pos);
	// 		}
	// 		client.content.append(client.tmp);
	// 		client.flag = false;
	// 		client.h = 1;
	// 	}
	// 	client.content_length = client.content.length();
	// 	if (client.content_length > 1024) {
	// 		client.content = client.content.substr(0,1024);
	// 		client.tmp = client.content.substr(1025);
	// 		client.chunk_size -= client.content.length();
	// 		client.flag = true;
	// 		client.h = 1;
	// 		client.hex_pos = _body.find("\r\n", client.next_crlf_pos) + 2;
	// 		client.crlf_pos = _body.find("\r\n", client.next_crlf_pos + 2);
	// 		if (client.hex_pos != std::string::npos && client.crlf_pos != std::string::npos) {
	// 			client._hex = _body.substr(client.hex_pos, client.crlf_pos);
	// 		}
	// 		return;
	// 	}
	// 	else{
	// 		client.chunk_size -= client.content.length();
	// 		client.hex_pos = _body.find("\r\n", client.next_crlf_pos) + 2;
	// 		client.crlf_pos = _body.find("\r\n", client.next_crlf_pos + 2);
	// 		if (client.hex_pos != std::string::npos && client.crlf_pos != std::string::npos) {
	// 			client._hex = _body.substr(client.hex_pos, client.crlf_pos);
	// 		}
	// 		client.h = 1;
	// 	}
	// 	client.body.append(client.content);
	// 	out << client.body << std::endl;
	// 	// std::cout << "chunk_size = " << chunk_size << std::endl;
	// 	// std::cout << "content_length = " << content_length << std::endl;
	// 	// client.hex_pos +=2;
	// 	if (client.chunk_size == 0) {
	// 		// client.chuDone = true;
	// 		// client.bodyReady = true;
	// 		return;
	// 	}
	// 		// break ;
	// }
	// else {
	// 	client.bodyReady = true;
	// 	// client.ready = true;
	// }
	// std::cout << "------------------------------\n";
	// // std::cout << "\r\n12\r\n" << std::endl;
	// std::cout << "1|" << _body << "|2" << std::endl;
	// std::cout << "------------------------------\n";
	// out << _body;
	// std::size_t start_pos = _body.find("\r\n") + 2;
    // std::size_t end_pos = _body.find("\r\n", start_pos);
    // std::string chunk_str = _body.substr(start_pos, end_pos - start_pos);

    // out << client.body << std::endl;
	// exit(0);



	// if (hex == 0)
	// 	client.chuDone = true;
	
}


size_t getFileSize(int fd) {
    long size;
    if (lseek(fd, 0, SEEK_END) != -1) { // move file pointer to the end of file
        size = lseek(fd, 0, SEEK_CUR); // get current file pointer position, which is the size of the file
        lseek(fd, 0, SEEK_SET); // move file pointer back to the beginning of the file
        return static_cast<size_t>(size); // convert size to size_t and return
    }
    // return 0 if lseek failed
    return 0;
}

void Server::read_from_socket_client(Client &client)
{
	char line[1024];
	memset(line,'\0',1024);
	int i = recv(client.fd_client, line, 1023, 0);
	line[i] = '\0';
	std::ofstream out("bood");
	// client.request += std::string(line);
	// if (!client.request.c_str())
	// {
	//     std::cerr<<"Dosen't found any request to work on it";
	//     exit(1);
	// }
	if (!client.alrChecked) {
		client.ret = is_carriage(std::string(line));
		client.header = std::string(line).substr(0, client.ret);
		client.parse.parse_request(client.header);
		client.b_pos = client.ret + 2;
		client.isChuncked = checkifchuncked(client.header);
		client.j = 1;
		client.alrChecked = true;
	}

	if (!client.isChuncked) {
		std::string _body(line);
		if (client.j) {
			std::string holder = _body.substr(client.b_pos, i);
			write(client.file, holder.c_str(), holder.length());
			if (getFileSize(client.file) == (size_t)std::atoi(client.parse._data["Content-Length"].c_str()))
				client.bodyReady = true;
			client.j = 0;
		}
		else {
			write(client.file, _body.c_str(), _body.length());
			if (getFileSize(client.file) == (size_t)std::atoi(client.parse._data["Content-Length"].c_str()))
				client.bodyReady = true;
		}
			// client.body += _body;
	}
	else if (client.isChuncked) {
		std::string _body(line);
		std::string tmp;
		if (client.j) {
			std::string s =  _body.substr(client.b_pos, i);
			handel_chunked(client, s, s.length());
			client.j = 0;
		}
		else
			handel_chunked(client, _body.c_str(), _body.length());
		if (client.chunk_size == 0)
			client.bodyReady = true;
	} 

	if (i != 1024) {
		out << client.body;
		out.close();
	    client.ready = true;
	}

	//  std::cout<<client.ready <<std::endl;
	// std::cout<<"******************"<<client.request<<"\n\n"<<std::endl;
	//exit(1);
}

// char *read_from_file(std::string file, Client &client)
// {
// 	char *str;
// 	str = (char *)malloc(sizeof(char) * 1024);
//     memset(str, 0, 1024);
//     if (client.start_writting == 1)
// 	    client.fd_file = open (file.c_str(),O_RDONLY);
// 	int i = read(client.fd_file,str,1024);
// 	str[i] = '\0';
//     if (i < 1024)
//         client.start_writting = 1;
// 	return (str);
// }

void Server::write_in_socket_client(std::string str, std::string file , Client &client)
{
	char *s;
	s = (char *)malloc(sizeof(char) * 1024);
    memset(s, '\0', 1024);
    int i = str.length();
    if (client.start_writting == 1)
    {
	    client.fd_file = open (file.c_str(),O_RDONLY);
        if (client.fd_file == -1)
        {
            client.is_delete = true;
           // exit(0);
        }
        client.start_writting = 0;
    }
    else if (client.start_writting == 0)
    {
        i = read(client.fd_file,s,1023);
        str = s;
    }
    if (write(client.fd_client,str.c_str(),i) < 1)
    {
        client.is_delete = true;
        free(s);
        return;
    }
    if (i <= 0)
    {
        client.is_delete = true;
        return;
    }
    free(s);
}


fd_set Server::initializer()
{
	FD_ZERO(&current);
	return (current);
}