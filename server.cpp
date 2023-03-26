
#include"http.hpp"
Server::Server(){
    
}


Server::~Server(){

}
void Server::read_from_socket_client(Client &client)
{
    char line[1024];

    memset(line,'\0',1024);
    int i = recv(client.fd_client, line, 1024, 0);
    line[i] = '\0';
    client.request += std::string(line);
    if (!client.request.c_str())
    {
        std::cerr<<"Dosen't found any request to work on it";
        exit(2);
    }
    if (i != 1024)
        client.ready = true;
     std::cout<<client.ready <<std::endl;
     //std::cout<<"\n\n"<<client.request<<"\n\n"<<std::endl;
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
        client.start_writting = 0;
    }
    else
    {
        i = read(client.fd_file,s,1023);
        std::cout<<"HI"<<std::endl;
        printf("%s\n",s);
        std::cout<<i<<std::endl;
        std::string body = s;
        str = body;
    }
   printf("size readed = %d  body ==== %s\n",i, str.c_str());

    if (write(client.fd_client,str.c_str(),i) < 1)
    {
        client.is_delete = true;
        free(s);
        return;
    }
    if (i <= 0)
    {
        std::cout << "here11\n";
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