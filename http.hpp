#ifndef HTTP_HPP
#define HTTP_HPP
#include <sys/socket.h>
#include <sys/types.h>
#include<netinet/in.h>
#include <string.h>
#include <unistd.h>
#include<iostream>
#include <string>
#include <stdlib.h>
#include<fcntl.h>
#include <vector>
#include <map>
#include <sstream>
#include <cerrno>
#include <fstream>
#include <string>
#include <list>
#include "parseRequest.hpp"
#include "client.hpp"
#include "server.hpp"
#include "response.hpp"

typedef struct s_hcode {
    std::string location;
    std::string root;
    // std::string 
} t_hcode;

class Http{
    public:
    Http();
    int fd_server;
    struct sockaddr_in def_socket;
    void create_socket();
    void naming_socket(struct sockaddr_in address);
    void bind();
    ~Http();
};
#endif