#ifndef CLIENT_HPP
#define CLIENT_HPP
class Client{
    public:
    Client(){
        address_length = sizeof(addresStorage);
    };
    ~Client(){};
    int fd_client;
    std::string request;
    std::string response;
    int position;
    socklen_t 				address_length;
	struct sockaddr_storage addresStorage;
};
#endif