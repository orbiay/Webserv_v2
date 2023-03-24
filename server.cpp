#include"http.hpp"
Server::Server(){
    
}


Server::~Server(){

}
void Server::read_from_socket_client(Client &client)
{
    char line[10];

    memset(line,'\0',10);
    int i = recv(client.fd_client, line, 10, 0);
    line[i] = '\0';
    client.request += std::string(line);
    if (!client.request.c_str())
    {
        std::cerr<<"Dosen't found any request to work on it";
        exit(2);
    }
    if (i != 10)
        client.ready = true;
    std::cout<<client.ready <<std::endl;
    std::cout<<"\n\n"<<client.request<<"\n\n"<<std::endl;
}

char *read_from_file(std::string file)
{
	char *str;
	str = (char *)malloc(sizeof(char) * 11383);
	int fd = open (file.c_str(),O_RDONLY);
	int i = read(fd,str,11382);
	str[i] = '\0';
	return (str);
}

void Server::write_in_socket_client(std::string str,std::string file ,const Client &client)
{
    char *s = read_from_file(file);
    str += s;
    write(client.fd_client,str.c_str(),strlen(str.c_str()));
}


fd_set Server::initializer()
{
    FD_ZERO(&current);
    return (current);
}