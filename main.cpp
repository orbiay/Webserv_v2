#include "http.hpp"
#include <iostream>
#include<array>
#include<list>
#include"./parsing/config.hpp"
#include"./parsing/Webserv.hpp"

#define num_of_servers 5




bool Http::finish = false;

int	parsing(int argc, char **argv, char **env);

int create_socket_and_bind_it(int i,std::vector<struct sockaddr_in>  &addr,Pserver server)
{
	(void)i;
	struct sockaddr_in address;

	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr =  htonl(INADDR_ANY);
	address.sin_port = htons(server.port);

	addr.push_back(address);

	Http http;
	http.create_socket();
	http.naming_socket(address);
	http.bind();
	return(http.fd_server);
}


std::vector<int> create_servers(std::vector<struct sockaddr_in>  &sed_struct ,std::vector<Pserver> servers)
{
	std::vector<int> servers_id;
	int i = 0;
	std::vector<Pserver>::iterator iter = servers.begin();
	int num_srver = servers.size();
	while (i < num_srver)
	{
		servers_id.push_back(create_socket_and_bind_it(i,sed_struct,*iter));
		i++;
		iter++;
	}
	return (servers_id);
}

void listen_for_conection(Server &server)
{
	if (::listen (server.fd_serv,100) < 0)
	{
		std::cerr<<"fialed listen ."<<std::endl;
		exit(2);
	}
	std::cout<<"the server "<< server.fd_serv << " in listen mode "<< "with port "<< server.server_config.port<<std::endl;
}

Client accept_new_connection(Server &server)
{
	Client client;
	client.fd_client = ::accept(server.fd_serv, (struct sockaddr *)&client.addresStorage, &client.address_length);
	if (client.fd_client == -1)
	{
	   std::cerr<<"failed accept method."<<std::endl;
		exit(EXIT_FAILURE);
	}
	if (Server::maxfd < client.fd_client)
		Server::maxfd = client.fd_client;
	FD_SET(client.fd_client, &Server::current);
	client.position = 0;
	sleep(1);
	return (client);
}

// int	checkifchuncked(std::string request) {
// 	std::vector<std::string> output;
// 	std::string token;
// 	std::stringstream ss(request);
// 	while (std::getline(ss, token, '\n')) {
// 		output.push_back(token);
// 	}
// 	std::vector<std::string>::iterator it;
// 	for (it = output.begin(); it != output.end(); it++){
// 		std::string tmp = *it;
// 		if (tmp.find("Transfer-Encoding: chunked")) {
// 			return 1;
// 		}
// 	}
// 	return 0;
// }

void parse_chuncked(Client &client) {

	// int decimal_number = std::stoi(hex_number, 0, 16)
	// client.tmp_body;
	// if (std::stoi())
	std::string token;
	std::stringstream ss(client.tmp_body);
	// while (std::getline(ss, token, '\n')) {
		//check if the token is "\r\nhex_num" and skip it if it's not 0 

		//else if it it's normal string from the body then insert it into client.body 1kb by 1kb

		// if (std::stoi(token, 0, 16) == 0) {
		// 	client.bodyReady = true;
		// 	return;
		// }
		// else if (std::stoi(token, 0, 16) != 0)
	// }
	
}

// void	Client::split_request(std::string request) {

// 	std::ofstream header("./header");
// 	std::ofstream req_body("./req_body");
// 	// std::stringstream ss(request);
// 	// while (std::getline(ss, token, "")) {
// 	// std::cout << "----------------Req----------------\n";
// 	// std::cout << request << std::endl;
// 	// std::cout << "----------------Req----------------\n";
// 	// }
// 	if (checkifchuncked(request)) {
// 		printf("it's chunckerd\n");
// 		if (!this->chunck_done) {
// 			size_t pos = request.find("\r\n\r\n");
// 			this->header = request.substr(0, pos+4); // Include the final CRLF
// 			this->tmp_body = request.substr(pos+4);
// 			header << this->header << std::endl;
// 			req_body << this->tmp_body << std::endl;
// 		}
// 		if (!this->bodyReady)	
// 			parse_chuncked(*this);
// 	}
// 	else {
// 		size_t pos = 0;
// 		std::string f = "\r\n\r\n";
// 		std::string token;
// 		while ((pos = request.find(f)) != std::string::npos) {
// 			token = request.substr(0, pos);
// 			this->header = token;
// 			// std::cout << "heder :\n" << token << std::endl;
// 			request.erase(0, pos + f.length());
// 		}
// 		this->body = request;
// 		this->bodyReady = true;
// 	}
// 	// std::ofstream out("body");
// 	// std::cout << "------------------b---------------------------\n";
// 	// out  << request << std::endl;
// 	// std::cout  << request << std::endl;
// 	// std::cout << "------------------b---------------------------\n";
// }

void run_server(std::vector<Server> &server_list)
{
   
	int ret = 0;
	while (1)
	{
		fd_set writable = Server::current;
		fd_set readable = Server::current;
		ret = select(Server::maxfd + 1, &readable, &writable, nullptr, 0);
		if (ret < 0) {
			std::perror("Error ");
			exit(EXIT_FAILURE);
		}
		if (!ret)
			continue;
		for (int  j = 0; j < (int)server_list.size(); j++)
		{
			Server &server = server_list[j];
		// }
		// while (server_iter != server_list.end())
		// {
			// If Statement for new connection.
			if (FD_ISSET(server.fd_serv, &readable))
			{
				// std::cout<<"Statement for new connection\n";
				// std::cout<< "server Fd = " << server.fd_serv <<"\n\n"<<std::endl;
				server.clients.push_back(accept_new_connection(server));
				// std::cout<<"The server number "<< server.fd_serv << " accept new connection seccesfully\n\n"<<std::endl;
			}
			for (int i = 0; i < (int)server.clients.size(); i++)
			{
				Client &client = server.clients[i];
				// IF statement for Request.
				if (FD_ISSET(client.fd_client, &readable))
				{
					// std::cout<<"statement for Request.\n";
					fcntl(client.fd_client, F_SETFL, O_NONBLOCK);
					server.read_from_socket_client(client);
					// std::cout<<"-----------------------"<<std::endl;
					// std::cout<<client.request<<std::endl;
					// std::cout<<"-----------------------"<<std::endl;
					if (client.ready /*&& (!client.request.empty())*/)
					{
						// client.split_request(client.request);
						// client.parse.parse_request(client.header);
						// client.parse.display_request(client.parse);
					}
					// else if (client.request.empty())
					// {
					// 	client.is_delete = true;
					// 	close(client.fd_client);
					// 	FD_CLR(client.fd_client,&server.current);
					// 	server.clients.erase(std::next(server.clients.begin(), i));
					// 	std::cout << "The client dropped successfully \n";
					// 	i--;
					// 	break;
					// }
				}
				// IF statement for Response.
				else if(i >= 0 && client.ready && FD_ISSET(client.fd_client, &writable))
				{
					if (client.bodyReady) {
						// std::cout << "heeeere\n" << std::endl;
						client.parse.check_request(server, client);
						if (client.is_delete == true)
						{
							//server.write_in_socket_client("HTTP/1.1 201 OK\nContent-Type: text/html\nContent-Length: 215\r\n\r\n","201success.html",client);
							close(client.fd_client);
							FD_CLR(client.fd_client,&server.current);
							server.clients.erase(std::next(server.clients.begin(), i));
							std::cout << "The client droped secsusfully \n";
							i--;
						}
					}
				}
			}
		}
	}
}
Server init_server(int id_servers,struct sockaddr_in addr,Pserver &server_config){
	Server server;
	server.fd_serv = id_servers;
	FD_ZERO(&server.readable);
	FD_ZERO(&server.writable);
	FD_SET(server.fd_serv, &Server::current);

	Server::maxfd = std::max(server.fd_serv, Server::maxfd);
	server.sizeof_struct = sizeof(addr);
	server.address = addr;
	server.server_config = server_config;
	return (server);
}


fd_set Server::current = Server::initializer();
int Server::maxfd = 0;

int main (int ac, char **av, char **env)
{
	try
	{
		Config conf(av);
		if (parsing (ac, av, env) == 1)
			return (1);
		int i = 0;
		int num_srver = conf.s.size();
		std::vector<struct sockaddr_in>  sed_struct;

		std::vector<int> id_servers;

		id_servers = create_servers(sed_struct,conf.s);
	  


		std::vector<Server> server_list;
		std::vector<Server>::iterator iter;
		std::vector<Pserver>::iterator iter_conf = conf.s.begin();
		while (i < num_srver)
		{
			server_list.push_back(init_server(id_servers[i],sed_struct[i],*iter_conf));
			//std::cout<<id_servers[i]<<std::endl;
			i++;
			iter_conf++;
		}
		iter = server_list.begin();
		while(iter != server_list.end())
		{
			listen_for_conection(*iter);
			iter++;
		}
		run_server(server_list);
	}
	catch(std::exception &e)
	{
		std::cout << "Error : " << e.what() << std::endl;
	}
}
