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

class Response {
	private:
		parseRequest _parse;
	public:
		
		Response();
		Response(const Response &r);
		Response operator = (const Response &r);
		~Response();

		void Get(Server &server, const Client &client, const parseRequest &parse);
		void Post(Server &server, const Client &client, const parseRequest &parse);
		void Delete(Server &server, const Client &client, const parseRequest &parse);	
};

#endif