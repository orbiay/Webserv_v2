#include "http.hpp"
#include <iostream>
#include<array>
#include<list>

#define num_of_servers 5
#define PORT 8011

int	parsing(int argc, char **argv);

int create_socket_and_bind_it(int i,struct sockaddr_in &addr)
{
	struct sockaddr_in address;

	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr =  htonl(INADDR_ANY);
	address.sin_port = htons(PORT + i);

	addr = address;

	Http http;
	http.create_socket();
	http.naming_socket(address);
	http.bind();
	return(http.fd_server);
}


std::array<int,num_of_servers> create_servers(std::array<struct sockaddr_in,num_of_servers>  &sed_struct)
{
	std::array<int,num_of_servers> servers_id;
	int i = 0;
	while (i < num_of_servers)
	{
		servers_id[i] = create_socket_and_bind_it(i,sed_struct[i]);
		i++;
	}
	return (servers_id);
}

void listen_for_conection(int fd_server)
{
	if (::listen (fd_server,100) < 0)
	{
		std::cerr<<"fialed listen ."<<std::endl;
		exit(2);
	}
	std::cout<<"the server "<< fd_server << " in listen mode\n\n"<<std::endl;
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

void	Client::split_request(std::string request) {

	// std::stringstream ss(request);
	// while (std::getline(ss, token, "")) {
	// }
	size_t pos = 0;
	std::string f = "\r\n\r\n";
	std::string token;
	while ((pos = request.find(f)) != std::string::npos) {
		token = request.substr(0, pos);
		this->header = token;
		// std::cout << "heder =÷\ " << token << std::endl;
		request.erase(0, pos + f.length());
	}
	this->body = request;
	// std::cout << "------------------b---------------------------\n";
	// std::cout << "body = " << request << std::endl;
	// std::cout << "------------------b---------------------------\n";
}

void run_server(std::list<Server> &server_list)
{
   
	std::list<Client>::iterator iter;
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
		std::list<Server>::iterator server_iter = server_list.begin();
		while (server_iter != server_list.end())
		{
			// If Statement for new connection.
			if (FD_ISSET(server_iter->fd_serv, &readable))
			{
				std::cout<<"Statement for new connection\n";
				std::cout<< "server Fd = " << server_iter->fd_serv <<"\n\n"<<std::endl;
				server_iter->clients.push_back(accept_new_connection(*server_iter));
				std::cout<<"The server number "<< server_iter->fd_serv << " accept new connection seccesfully\n\n"<<std::endl;
			}
			for (int i = 0; i < (int)server_iter->clients.size(); i++)
			{
				Client &client = server_iter->clients[i];
				// IF statement for Request.
				if (FD_ISSET(client.fd_client, &readable))
				{
					std::cout<<"statement for Request.\n";
					server_iter->read_from_socket_client(client);
					if (client.ready)
					{
						client.split_request(client.request);
						client.parse.parse_request(client.header);
						client.parse.display_request(client.parse);
					}
				}
				// IF statement for Response.
				else if(i >= 0 &&  FD_ISSET(client.fd_client, &writable))
				{
					std::cout<<"statement for Response.\n";
					client.parse.check_request(*server_iter, client);
					// server_iter->write_in_socket_client("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 214\r\n\r\n","404error.html",client);
					close(client.fd_client);
					FD_CLR(client.fd_client,&server_iter->current);
					server_iter->clients.erase(std::next(server_iter->clients.begin(), i));
					i--;
				}
			}
			server_iter++;
		}
	}
}
Server init_server(int id_servers,struct sockaddr_in addr){
	Server server;
	server.fd_serv = id_servers;
	FD_ZERO(&server.readable);
	FD_ZERO(&server.writable);
	//std::cout << "socket fd = "  << server.fd_serv << std::endl;
	FD_SET(server.fd_serv, &Server::current);

	Server::maxfd = std::max(server.fd_serv, Server::maxfd);
	server.sizeof_struct = sizeof(addr);
	//std::cout<<server.sizeof_struct<<std::endl;
	server.address = addr;
	return (server);
}


fd_set Server::current = Server::initializer();
int Server::maxfd = 0;

int main (int ac, char **av)
{
	parsing(ac, av);
	int i = 0;
	std::array<struct sockaddr_in,num_of_servers>  sed_struct;

	std::array<int, num_of_servers> id_servers;

	id_servers = create_servers(sed_struct);
  


	std::list<Server> server_list;
	std::list<Server>::iterator iter = server_list.begin();
	while (i < 5)
	{
		server_list.push_back(init_server(id_servers[i],sed_struct[i]));
		//std::cout<<id_servers[i]<<std::endl;
		i++;
	}
	iter = server_list.begin();
	while(iter != server_list.end())
	{
		listen_for_conection(iter->fd_serv);
		iter++;
	}
	run_server(server_list);
}