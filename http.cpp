/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:36:47 by fbouanan          #+#    #+#             */
/*   Updated: 2023/03/17 18:36:59 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"http.hpp"

Http::Http(){

}

void Http::create_socket()
{
    fd_server = ::socket(AF_INET,SOCK_STREAM,0);
    if (fd_server == -1)
    {
        std::cerr<<"can't Create a socket."<<std::endl;
        exit(2);
    }
    fcntl(fd_server, F_SETFL, O_NONBLOCK);
}

void Http::naming_socket(struct sockaddr_in address )
{
    def_socket = address;
}

void Http::bind(Pserver &conf)
{
    int use = 1;
    struct addrinfo hints;
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_INET; 
    hints.ai_socktype = SOCK_STREAM; 
    struct addrinfo* results;
    setsockopt(fd_server,SOL_SOCKET,SO_REUSEADDR, &use,sizeof(use));
    std::cout<<conf.host.c_str()<<std::endl;
    int status = getaddrinfo(conf.host.c_str(), "http", &hints, &results);
    if (status != 0) {
        std::cerr << "Failed to perform DNS lookup: " << gai_strerror(status) << std::endl;
         exit(2); ;
    }
    if (::bind(fd_server,(struct sockaddr *)&def_socket,sizeof(def_socket)) < 0)
    {
        std::cerr<<"can't bind socket with def_socket."<<std::endl;
        exit(2);
    }
}

Http::~Http(){

}