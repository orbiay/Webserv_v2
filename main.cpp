#include "http.hpp"
#include <iostream>
#include<array>
#include<list>

#define num_of_servers 5
#define PORT 8011

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
    std::cout<<"the server "<< fd_server << " in listen mode"<<std::endl;
}

Client accept_new_connection(Server &server)
{
    Client client;
    client.fd_client = ::accept(server.fd_serv, (struct sockaddr *)&server.address, &server.sizeof_struct);
    if (client.fd_client == -1)
    {
       std::cerr<<"failed accept method."<<std::endl;
        exit(EXIT_FAILURE);
    }
    if (server.maxfd < client.fd_client)
        server.maxfd = client.fd_client;
    FD_SET(client.fd_client, &server.current);
    client.position = 0;
    sleep(1);
    return (client);
}

void run_server(Server &server)
{
    listen_for_conection(server.fd_serv);
    std::list<Client>::iterator iter = server.clients.begin();
    int ret;
    while (1)
    {
        server.writable = server.current;
        server.readable = server.current;
        ret = select(server.maxfd + 1, &server.readable, &server.writable, nullptr, nullptr);
        if (ret < 0) {
			std::perror("Error ");
			exit(EXIT_FAILURE);
		}
		if (!ret)
			continue ;
        for(int fd = server.fd_serv; fd <= server.maxfd;++fd)
        {
            if (FD_ISSET(fd, &server.readable))
            {
                //exit(1);
                //statement for new connection
                if (fd == server.fd_serv)
                {
                    server.clients.push_back(accept_new_connection(server));
                    std::cout<<"The server number "<< server.fd_serv << " accept new connection seccesfully"<<std::endl;
                }
                else {
                    //statement for request
                    for (iter = server.clients.begin();iter != server.clients.end();iter++)
                    {
                        std::cout<<fd<<std::endl;
                        if (iter->fd_client == fd)
                        {
                            server.read_from_socket_client(*iter);
                            // parse the request
                            iter->parse.parse_request(iter->request);
                            iter->parse.display_request(iter->parse);
                            break;
                        }
                    }
                }
            }
            //statement for Response
            if(FD_ISSET(fd, &server.writable))
            {
                //iter = it;
                for (iter = server.clients.begin();iter != server.clients.end();iter++)
                {
                    if (iter->fd_client == fd)
                    {
                        // check the request and response with error page if there is any
                        iter->parse.check_request(server, *iter);
                        server.write_in_socket_client("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 214\r\n\r\n","404error.html",*iter);
                        close(fd);
                        FD_CLR(fd,&server.current);
                        break;
                    }
                }
            }
        }
    }
}
Server init_server(int id_servers,struct sockaddr_in addr){
    Server server;
    server.fd_serv = id_servers;
    FD_ZERO(&server.current);
    FD_ZERO(&server.readable);
    FD_ZERO(&server.writable);
    FD_SET(server.fd_serv, &server.current);
    server.maxfd = id_servers;
    server.sizeof_struct = sizeof(addr);
    std::cout<<server.sizeof_struct<<std::endl;
    server.address = addr;
    return (server);
}

int main ()
{
    int i = 0;

    std::array<struct sockaddr_in,num_of_servers>  sed_struct;

    std::array<int, num_of_servers> id_servers;

    id_servers = create_servers(sed_struct);

    std::list<Server> server_list;

    std::list<Server>::iterator iter;

    while (i < 5)
    {
        server_list.push_back(init_server(id_servers[i],sed_struct[i]));
        std::cout<<id_servers[i]<<std::endl;
        i++;
    }
    iter = server_list.begin();
    for(std::list<Server>::iterator it = server_list.begin(); it != server_list.end();it++)
    {
        //std::cout<<it->fd_serv<<std::endl;
        run_server(*it);
        //if (it++ == client_list.end())
        it = iter;
    }
    //while (i < num_of_servers)
    //{
    //    //std::cout<<id_servers[i]<<std::endl;
    //    run_server(client_list);
    //    if (i + 1 == num_of_servers)
    //        i = 0;
    //}
}