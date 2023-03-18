/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:44:40 by fbouanan          #+#    #+#             */
/*   Updated: 2023/03/17 18:35:44 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http.hpp"

Response::Response() {
	
}

// Response::Response(const parseRequest &parse) {
//     this->_parse = parse;
// }

Response::Response(const Response &r) {
	*this = r;
}

Response Response::operator=(const Response &r) {
	this->_parse = r._parse;
	return *this;
}

void Response::Get(Server &server, const Client &client, const parseRequest &parse) {
	(void)parse;
	(void)client;
	(void)server;
}

void Response::Post(Server &server, const Client &client, const parseRequest &parse) {
	(void)parse;
	(void)client;
	(void)server;
	int upload = 1;
	if (upload) {
		
	}
}

void Response::Delete(Server &server, const Client &client, const parseRequest &parse) {
	(void)parse;
	(void)client;
	(void)server;
}

Response::~Response() {
	
}
