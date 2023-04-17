#include "http.hpp"
#include <iostream>
#include<array>
#include<list>
#include"./parsing/config.hpp"
#include"./parsing/Webserv.hpp"

#define num_of_servers 5
int parsing(int argc, char **argv, char **env);
bool Http::finish = false;

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
	//sleep(1);
	return (client);
}

void run_server(std::vector<Server> &server_list)
{
   
	int ret = 0;
	while (1)
	{
		fd_set writable = Server::current;
		fd_set readable = Server::current;
		ret = select(Server::maxfd + 1, &readable, &writable, nullptr, 0);
		//std::cout<<"max=========== "<<Server::maxfd<<std::endl;
		if (ret < 0) {
			std::perror("select() Error ");
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
				server.clients.push_back(accept_new_connection(server));
			}
			for (int i = 0; i < (int)server.clients.size(); i++)
			{
				Client &client = server.clients[i];
				// IF statement for Request.
				if (FD_ISSET(client.fd_client, &readable))
				{
					fcntl(client.fd_client, F_SETFL, O_NONBLOCK);
					server.read_from_socket_client(client);
				}
				// IF statement for Response.
				else if(i >= 0  && FD_ISSET(client.fd_client, &writable))
				{
					if (client.bodyReady) {
						client.parse.check_request(server, client);
						if (client.is_delete == true)
						{
							FD_CLR(client.fd_client,&server.current);
							if (close(client.fd_client) != 0 || close(client.file) != 0)
								perror("close() failed");
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
Server init_server(int id_servers,struct sockaddr_in addr,Pserver &server_config, Config &conf){
	Server server;
	server.body_size = conf.body_size;
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
		signal(SIGPIPE, SIG_IGN);
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
			server_list.push_back(init_server(id_servers[i],sed_struct[i],*iter_conf, conf));
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
