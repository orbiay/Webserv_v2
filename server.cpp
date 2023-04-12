
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
	int reades = 0;;
	client._body = _body;
	std::string *n_hex = new std::string();
	client._hex = (char *)n_hex->c_str();
	client.hex_ready = false;
	while (reades < i) {
		if (!client.chunk_size) {
			while (reades < i) {
				client._hex[client.hex_len++] = client._body[reades++];
				if (findHex(client))
					break;
			}
			if (!client.hex_ready)
				break;
			// std::cout << "|" << client._hex <<c "|" << std::endl;
			client.chunk_size =  std::strtoul(client._hex, nullptr, 16);;
			client.hex_len = 0;
			if (!client.chunk_size) {
				close(client.file);
				client.bodyReady = true;
				break;
			}
		}
		while (reades < i && client.chunk_size) {
			// std::cout << "|" << client._body + reades << "|" << std::endl;
			write(client.file ,client._body + reades, 1);
			client.chunk_size--;
			reades++;
		}
	}
	delete(n_hex);
}


// size_t getFileSize(int fd) {
//     long size;
//     if (lseek(fd, 0, SEEK_END) != -1) { // move file pointer to the end of file
//         size = lseek(fd, 0, SEEK_CUR); // get current file pointer position, which is the size of the file
//         lseek(fd, 0, SEEK_SET); // move file pointer back to the beginning of the file
//         return static_cast<size_t>(size); // convert size to size_t and return
//     }
//     // return 0 if lseek failed
// }

size_t	getFileSize(const std::string& name)
{
	// struct stat	fileStat;
	// lstat(name.c_str(), &fileStat);
	// return fileStat.st_size;
	std::ifstream file(name, std::ifstream::ate | std::ifstream::binary);
	size_t size = 0;
    if (file.is_open())
	{
       	size = file.tellg();
		file.close();
	}
    else {
		file.close();
		//exit(0);
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
	char line[1024];
	memset(line,'\0',1024);
	int i  = recv(client.fd_client, line, 1023, 0);
	std::cout << "i = " << i << std::endl;
	line[i] = '\0';
	// client.read_size += i;
	// client.request += std::string(line);
	// if (!client.request.c_str())
	// {
	//     std::cerr<<"Dosen't found any request to work on it";
	//     exit(1);
	// }
	// if rtequest doesn't exist chenge is_delete variable to true for drop it.
	if (!client.alrChecked) {
		client.ret = is_carriage(std::string(line), client);
		if (client.readyToParse) {
			client.header = std::string(line).substr(0, client.ret);
			client.parse.parse_request(client.header);
			client.b_pos = client.ret + 4;
			client.isChuncked = checkifchuncked(client.header);
			client.j = 1;
			client.alrChecked = true;
		}
		else
		{
			client.is_delete = true;
			return;
		}
		// if (!client.isChuncked)
		// if (client.isChuncked)
		// 	client.b_pos = client.ret + 2;
			
	}

	if (!client.isChuncked) {
		// std::string _body(line);
		if (client.j) {
			// std::string holder = _body.substr(client.b_pos, i);
			char *holder;
			holder = substr_no_null(line, client.b_pos, i, i);
			if (getFileSize(client.file_name) < (size_t)std::atoi(client.parse._data["Content-Length"].c_str())) {
				write(client.file, holder, i - client.b_pos);
			}
			else {
				close(client.file);
				client.bodyReady = true;
				client.ready = true;
			}
			client.j = 0;
		}
		else {

			// std::cout << "file_size = " << getFileSize(client.file_name) << std::endl;
			// std::cout << "Content-Length = " << client.parse._data["Content-Length"] << std::endl;
			if (getFileSize(client.file_name) < (size_t)std::atoi(client.parse._data["Content-Length"].c_str())) {
				write(client.file, line, i);
			}
			else {
				close(client.file);
				client.bodyReady = true;
				client.ready = true;
			}
		}
			// client.body += _body;
	}
	else if (client.isChuncked) {
		// std::string _body(line);
		if (client.j) {
			// printf("here\n");
			client.b_pos -=2;
			char *holder;
			holder = substr_no_null(line, client.b_pos, i, i);
			// std::string s =  _body.substr(client.b_pos, i);
			// std::cout << "s = " << s << std::endl;
			handel_chunked(client, holder, i - client.b_pos);
			delete(holder);
			client.j = 0;
		}
		else
			handel_chunked(client, line, i);
		if (client.chunk_size == 0) {
			close(client.file);
			client.bodyReady = true;
		}
	} 
	// std::cout << "251045223 = " << std::atoi(client.parse._data["Content-Length"].c_str())<< std::endl;
	if (i < 1023 ) {
		client.bodyReady = true;
	    client.ready = true;
	}
}

void Server::write_in_socket_client(std::string str, std::string file , Client &client)
{
	char *s;
	s = new char[1024];
    memset(s, '\0', 1024);
    int i = str.length();
	//s = strdup(str.c_str());
    if (client.start_writting == 1)
    {
	    client.fd_file = open (file.c_str(),O_RDONLY);
        if (client.fd_file == -1)
        {
            client.is_delete = true;
           // exit(0);
        }
        client.start_writting = 0;
		write(client.fd_client,str.c_str(),strnlen(str.c_str(),1023));
		return ;
    }
    else if (client.start_writting == 0)
    {
        i = read(client.fd_file,s,1023);
        // std::cout<<"i = "<<i<<std::endl;
        //str = s;
    }
    write(1,"\n",1);
    if (write(client.fd_client,s,strnlen(s,1023)) < 1)
    {
        client.is_delete = true;
        close(client.fd_client);
		delete(s);
        return;
    }
    if (i <= 0)
    {
        client.is_delete = true;
        close(client.fd_client);
        return;
    }
   	delete(s);
}


fd_set Server::initializer()
{
	FD_ZERO(&current);
	return (current);
}