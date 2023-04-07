#include "http.hpp"

Client::Client() {
	address_length = sizeof(addresStorage);
	ready = false;
	start_writting = 1;
	fd_file = -1;
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
	// memset(_hex, 0, 1024);
	// file.open("fcc");
	file = open("fcc", O_CREAT | O_RDWR | O_APPEND, 0644);
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
