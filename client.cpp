#include "http.hpp"

std::string generateRandomString(int length) {
    const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    const int charsetSize = sizeof(charset) - 1;
    std::string randomString(length, ' ');

    std::srand(std::time(0)); // Seed the random number generator

    for (int i = 0; i < length; ++i) {
        randomString[i] = charset[std::rand() % charsetSize];
    }

    return randomString;
}

Client::Client() {
	read_size = 0;
	address_length = sizeof(addresStorage);
	ready = false;
	start_writting = 1;
	fd_file = -1;
	// post_fd = -1;
	is_delete = false;
	is_finish = false;
	enter = false;
	position = 0;
	isChuncked = false;
	bodyReady = false;
	alrChecked = false;
	chuDone = false;
	ret = 0;
	j = 0;
	h = 0;
	hex_pos = 0;
	flag = false;
	crlf_pos = 0;
	chunk_size = 0;
	content_length = 0;
	next_crlf_pos = 0;
	hex_len = 0;
	readyToParse = false;
	// memset(_hex, 0, 1024);
	// file.open("fcc");
	std::string m = "data/";
	file_name = m.append(generateRandomString(6));
	file_name.append(".mp4");
	std::cout << "fle_name = " << file_name << std::endl;
	file = open(file_name.c_str(), O_CREAT | O_RDWR | O_APPEND, 0644);
	std::cout << "file 1 = " << file << std::endl;
}

Client::~Client() {

}

// Client::Client(const Client &r) {
// 	*this = r;
// 	// (void)r;
// }

// Client Client::operator=(const Client &r) {
// 	(void)r;
// 	return *this;
// }
