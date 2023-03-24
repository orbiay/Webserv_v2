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
	public:
		Client			client;
		int				readed;
		int				content_length;
		bool			is_done;
		std::string		path;
		int				result;
		std::ifstream	is_exist;
		std::ofstream	outfile;
		
		Response();
		Response(const Response &r);
		Response operator = (const Response &r);
		Response(const Client &_client);
		~Response();

		void Get(Server &server);
		void Post(Server &server);
		void Delete(Server &server);	
};

#endif