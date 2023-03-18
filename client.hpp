#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "http.hpp"

class Client{
    public:
    Client(){
        address_length = sizeof(addresStorage);
        g = false;
    };
    ~Client(){};
    int fd_client;
    parseRequest parse;
    std::string request;
    std::string response;
    int position;
    bool g;
    
    socklen_t 				address_length;
	struct sockaddr_storage addresStorage;
};

#endif