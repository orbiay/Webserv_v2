/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:44:53 by fbouanan          #+#    #+#             */
/*   Updated: 2023/03/17 18:39:28 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "http.hpp"
#include "client.hpp"

class Client;

class Response{
		Response();
	public:
		Client			&client;
		int				readed;
		int				content_length;
		bool			is_done;
		std::string		path;
		int				result;
		std::ifstream	is_exist;
		int	outfile;
		
		Response(Client &client);
		Response(const Response &r);
		Response operator = (const Response &r);
		//Response(Client &_client);
		~Response();

		void Get(Server &server);
		void Post(Server &server, int flag);
		void Delete(Server &server);
		std::string getContentType(Server &server);
		int read_and_write(Client &client);
		void size_file(std::string file_name);
		int is_directory_or_file(std::string path);
		void autoindex_mode(bool &auto_index,std::string &default_index,std::string root,Server &server,Client &client);
		void file_handler(Server &server);
		void directory_handler(Server &server);
		bool check_if_exist(Server &server);
};

#endif