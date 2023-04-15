#ifndef SERVER_HPP
#define SERVER_HPP
#include"./parsing/location.hpp"
#include"./parsing/Webserv.hpp"
#include"./parsing/config.hpp"
#include"http.hpp"


class Server{
    public:
    Server();
    ~Server();
    void read_from_socket_client(Client &client);
    void write_in_socket_client(std::string str,std::string file ,Client &client);
    struct sockaddr_in address;
    int fd_serv;
    std::vector<Client> clients;
    static fd_set current;
    fd_set readable;
    fd_set writable;
    unsigned int     sizeof_struct;
    static int maxfd;
    Pserver server_config;
    size_t body_size;
    
    static fd_set initializer();
};


#endif
