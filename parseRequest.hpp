/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseRequest.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:40:24 by fbouanan          #+#    #+#             */
/*   Updated: 2023/03/16 13:04:30 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEREQUEST_HPP
#define PARSEREQUEST_HPP

#include <vector>
#include <map>
#include <sstream>
#include "http.hpp"

class Server;
class Client;

class parseRequest {
	private:
	public:
		int fd_client;
		std::map<std::string, std::string> _data;
		parseRequest();
		parseRequest(const parseRequest &data);
		parseRequest &operator = (const parseRequest &data);
		~parseRequest();
		
		std::map<std::string, std::string> getData();
		void	parse_request(std::string request);
		void	parse_infos(std::string _data);
		void	parse_url(std::string _url);
		void	check_request(Server &server, const Client &iter);
		void	display_request(parseRequest parse);
		void	check_methods(Server &server, const Client &Client);
};



#endif
