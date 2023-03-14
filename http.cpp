#include"http.hpp"
Http::Http(){

}

void Http::create_socket()
{
    fd_server = ::socket(AF_INET,SOCK_STREAM,0);
    if (fd_server == -1)
    {
        std::cerr<<"can't Create a socket."<<std::endl;
        exit(2);
    }
    fcntl(fd_server, F_SETFL, O_NONBLOCK);
}

void Http::naming_socket(struct sockaddr_in address )
{
    def_socket = address;
}

void Http::bind()
{
    if (::bind(fd_server,(struct sockaddr *)&def_socket,sizeof(def_socket)) < 0)
    {
        std::cerr<<"can't bind socket with def_socket."<<std::endl;
        exit(2);
    }
}

Http::~Http(){

}