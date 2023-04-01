#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "http.hpp"

class Client{
    public:
    Client(){
        address_length = sizeof(addresStorage);
        ready = false;
        start_writting = 1;
        fd_file = -1;
        is_delete = false;
        is_finish = false;
        enter = false;
        position = 0;
    };
    ~Client(){};
    int fd_client;
    parseRequest parse;
    std::string request;
    std::string response;
    int position;
    std::string header;
    std::string body;
    bool ready;
    int start_writting;
    int fd_file;
    bool is_delete;
    bool is_finish;
    bool enter;
    std::string   sizefile;
    std::string   extension;
    
    socklen_t 				address_length;
	struct sockaddr_storage addresStorage;

    void    split_request(std::string request);
};

#endif