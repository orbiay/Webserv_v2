#ifndef CLIENT_HPP
#define CLIENT_HPP
class Client{
    public:
    Client(){};
    ~Client(){};
    int fd_client;
    std::string request;
    std::string response;
    int position;
};
#endif