// if (is_directory(path)) {

		// }
		// std::ifstream is_exist(path);
		// if (!is_exist.is_open() || this->is_done) {
			// std::ofstream outfile;
			// outfile.open(path);
			// if (!outfile.is_open()) {
			// 	perror("error");
			// }
			if (content_length <= 1024) {
				printf("here 1\n");
				outfile << client->body.substr(this->readed, content_length);
				outfile.close();
				Http::finish = true;
				server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: 215\r\n\r\n","201success.html", *client);
			}
			else if (content_length > 1024) {
				printf("here 2\n");
				std::cout << this->readed << std::endl;
				outfile << client->body.substr(this->readed, 1024);
				this->is_done = true;
				content_length -= 1024;
				this->readed += 1024;
			}
			if (this->readed == content_length) {
				printf("here 3\n");
				outfile.close();
				this->is_done = false;
				Http::finish = true;
				std::cout << Http::finish << std::endl;
				server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: 215\r\n\r\n","201success.html", *client);
			}
		// }
		// if (is_exist.is_open()) {
		// 	printf("here 4\n");
		// 	server.write_in_socket_client("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 186\r\n\r\n","200exists.html", client);
		// }
		// std::cout << "--------___--------------body--------------------\n";
		// std::cout << client.body << std::endl;
		// std::cout << "--------------------------------------------\n";
		