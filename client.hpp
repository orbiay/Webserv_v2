#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "http.hpp"

class Client{
	public:
	Client();
	~Client();
	int read_size;
	int fd_client;
	parseRequest parse;
	std::string request;
	std::string response;
	int position;
	std::string header;
	std::string body;
	std::string	tmp_body;
	bool ready;
	int start_writting;
	int fd_file;
	bool is_delete;
	bool is_finish;
	bool enter;
	bool isChuncked;
	bool alrChecked;
	bool bodyReady;
	size_t ret;
	size_t b_pos;
	bool chuDone;
	int j;
	size_t hex_pos;
	std::string tmp;
	bool flag;
	size_t crlf_pos;
	size_t next_crlf_pos;
	char _hex[20];
	size_t hex_len;
	size_t chunk_size;
	size_t content_length;
	std::string content;
	std::string file_name;
	int h;
	char hex_c[10];
	// char *_body;
	std::string   sizefile;
    std::string   extension;
	int post_fd;
	bool readyToParse;

	bool hex_ready;
	int file;
	int check;
	
	/*************************/
    std::string url;
    std::string client_header;
    std::string content_type;
	std::string path;
    /*************************/
	socklen_t 				address_length;
	struct sockaddr_storage addresStorage;

	void    split_request(std::string request);
};

#endif