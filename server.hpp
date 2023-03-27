#ifndef SERVER_HPP
#define SERVER_HPP
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
    static fd_set initializer();
};


#endif
