#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "http.hpp"

class Client{
    public:
    Client(){};
    ~Client(){};
    int fd_client;
    parseRequest parse;
    std::string request;
    std::string response;
    int position;
};

#endif