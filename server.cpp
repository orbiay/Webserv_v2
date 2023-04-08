
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
				// std::cout << client._hex << std::endl;
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
	// if rtequest doesn't exist chenge is_delete variable to true for drop it.
	if (!client.alrChecked) {
		client.ret = is_carriage(std::string(line));
		client.header = std::string(line).substr(0, client.ret);
		client.parse.parse_request(client.header);
		if (!client.isChuncked)
			client.b_pos = client.ret + 4;
		if (client.isChuncked)
			client.b_pos = client.ret + 2;
			
		client.isChuncked = checkifchuncked(client.header);
		client.j = 1;
		client.alrChecked = true;
	}

	if (!client.isChuncked) {
		std::string _body(line);
		if (client.j) {
			std::string holder = _body.substr(client.b_pos, i);
			if (getFileSize(client.file) < (size_t)std::atoi(client.parse._data["Content-Length"].c_str())) {
				write(client.file, holder.c_str(), holder.length());
			}
			client.j = 0;
		}
		else {
			printf("kakaka\n");
			std::cout << "file size = " << getFileSize(client.file) << std::endl;
			std::cout << "Content-Length = " << client.parse._data["Content-Length"] << std::endl;
			if (getFileSize(client.file) < (size_t)std::atoi(client.parse._data["Content-Length"].c_str())) {
				write(client.file, _body.c_str(), _body.length());
			}
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
		if (client.chunk_size == 0) {
			close(client.file);
			client.bodyReady = true;
		}
	} 

	if (i != 1024) {
		out << client.body;
		out.close();
		client.bodyReady = true;
	    client.ready = true;
	}
}

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
        std::cout<<"i = "<<i<<std::endl;
        str = s;
    }
    write(1,"\n",1);
    if (write(client.fd_client,str.c_str(),i) < 1)
    {
        client.is_delete = true;
        close(client.fd_client);
        free(s);
        return;
    }
    if (i <= 0)
    {
        client.is_delete = true;
        close(client.fd_client);
        return;
    }
    free(s);
}


fd_set Server::initializer()
{
	FD_ZERO(&current);
	return (current);
}