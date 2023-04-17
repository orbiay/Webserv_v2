 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:39:32 by fbouanan          #+#    #+#             */
/*   Updated: 2023/03/18 18:01:33 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http.hpp"


parseRequest::parseRequest() {
	
}

parseRequest::parseRequest(const parseRequest &data)
{
	*this = data;
}

parseRequest::~parseRequest() {

}

parseRequest &parseRequest::operator=(const parseRequest &data) 
{
	this->_data = data._data;
	return *this;
}


void	parseRequest::parse_url(std::string _url)
{
	std::string token;
	std::stringstream ss(_url);
	while (std::getline(ss, token, ' ')) {
		if (token == "GET" || token == "POST" || token == "DELETE") {
			this->_data["method"] = token;
			// this->_data.insert(std::make_pair("method", token));
		}
		else if (token[0] == '/') {
			// this->_data.insert(std::make_pair("path", token));
			this->_data["path"] = token;
		}
		else {
			// this->_data.insert(std::make_pair("version", token));
			this->_data["version"] = token;
		}
	}
}

void	parseRequest::parse_infos(std::string _data)
{
	std::vector<std::string> output;
	std::string token;
	std::stringstream ss(_data);
	while (std::getline(ss, token, ' ')) {
		output.push_back(token);
	}
	if (output[0] == "Host:"){
		// this->_data["Host"] = output[1];
		this->_data.insert(std::make_pair("Host", output[1]));
	}
	else if (output[0] == "Content-Type:") {
		this->_data.insert(std::make_pair("Content-Type", output[1]));
	}
	else if (output[0] == "Content-Length:") {
		this->_data.insert(std::make_pair("Content-Length", output[1]));
	}
	else if (output[0] == "Transfer-Encoding:") {
		this->_data.insert(std::make_pair("Transfer-Encoding", output[1]));
	}
	else if (output[0] == "Accept:") {
		this->_data.insert(std::make_pair("Accept", output[1]));
	}
	else if (output[0] == "Accept-Encoding:")
	{
		this->_data.insert(std::make_pair("Accept-Encoding", output[0]));
	}
	else if (output[0] == "Host:")
	{
		this->_data.insert(std::make_pair("Host", output[1]));
	}
	else if (output[0] == "Cookie:")
	{
		this->_data.insert(std::make_pair("Cookie", output[1]));
	}
}

void	parseRequest::save_body(std::string req) {

	std::string token;
	std::stringstream ss(req);
	std::vector<std::string> tmp;
	while (std::getline(ss, token)) {
		tmp.push_back(token);
	}
	std::vector<std::string>::iterator it = tmp.begin();
	while (it != tmp.end()) {
		if (*it == "\n") {
			break;	
		}
		it++;
	}
	while (it != tmp.end()) {
		this->_body.push_back(*it);
		it++;
	}
}

void    parseRequest::parse_request(std::string request)
{
	// std::cout << "----------------------------------------------------" << std::endl;
	std::vector<std::string> output;
	std::string token;
	std::stringstream ss(request);
	while (std::getline(ss, token, '\n')){
		output.push_back(token);
	}
		parse_url(output[0]);
		std::vector<std::string>::iterator it;
		for (it = output.begin() + 1; it != output.end(); it++){
			parse_infos(*it);
		}

	// std::cout << "----------------------------------------------------" << std::endl;
}
		//--------------------------------checking request-------------------------------------------
int	check_url(std::string url)
{
	std::string::iterator it = url.begin();
	while (it != url.end()) {
		if (!isprint(*it)){
			return (1);
		}
		it++;
	}
	return (0);
}

int check_url_size (std::string url) {
	// printf("here\n");
	if (url.size() > 2048)
		return (1);
	return (0);
}

std::string get_pure_one(std::string &location_val,std::string url)
{
	// std::cout<<<<
	//if (location_val.lenght() == url.lenght())
	std::string::iterator c = url.begin() + location_val.length();
	std::string str;
	for(;c != url.end();c++)
		str.push_back(*c);//segfault if url is a directory
	//exit(0);
	return str;
}

int	matched_location(Server &server ,std::string url,Client &client)
{
	// printf("here\n");
	// std::cout << "url = " << url << std::endl;
	int i = 0;
	client.link_location = url;
	std::vector<Location>::iterator it = server.server_config.L.begin();
	std::vector<size_t> vec;
	Location save;
	bool flag = false;
	while (it != server.server_config.L.end()) {
		i = 0;
		Location &loc = *it;
		size_t pos = url.find(loc.location_val);
		if (pos != std::string::npos)
		{
			if (!flag) {
				save = loc;
				flag = true;
			}
			if (loc.location_val.length() >= save.location_val.length()) {
				save = loc;
			}
		}
		it++;
	}
	client.location = save;
	client.location.location_val = get_pure_one(client.location.location_val,url);
	// std::cout<<"locval =======>"<<client.location.location_val<<std::endl;
	// exit(0);
	// std::cout << "upload = " << save.upload << std::endl;
	if (save.location_val.empty())
		return (-1);
	return (0);
}
		//-------------------------------------------------------------------------------------------

int	is_file(Client &client) {
	std::string file = client.parse._data["path"];
	for (size_t i = 0; i < file.length(); i++) {
        if (file[i] == '.') {
            if (i+1 < file.length() && isalnum(file[i+1])) {
				return (1);
            } else {
                std::cout << "Dot is not followed by a character." << std::endl;
				return (0);
            }
        }
    }
	return (0);
}

int find_index(Server &server, std::string method) {
	int i = 0;
	while(i < 3) {
		if (server.server_config.methods[i] == method)
			return (1);
		i++;
	}
	return (0);
}

		//--------------------------------checking methods-------------------------------------------
void	check_methods(Server &server, Client &client)
{
	Response res(client);
	//res.client = &client;
	// res.client = client.parse;
	// std::cout << "method = " << server.server_config.methods[0] << std::endl;
	if (client.parse._data["method"] == "GET" && find_index(server, "GET")) {
		res.Get(server);
		//server.write_in_socket_client("HTTP/1.1 405 KO\nContent-Type: text/html\nContent-Length: 221\r\n\r\n","405error.html", client);
	}
	else if (client.parse._data["method"] == "POST" && find_index(server, "POST")) {
		if (is_file(client)) {
			res.Post(server, FILE);
			// res.Post(server);
		}
		else {
			res.Post(server, DIRE);
		}
	}

	else if (client.parse._data["method"] == "DELETE" && find_index(server, "DELETE")) {
		if (is_file(client)) {
			res.Delete(server, FILE);
		}
		else {
			res.Delete(server, DIRE);
		}
	}
	else {
		server.write_in_socket_client("HTTP/1.1 405 KO\nContent-Type: text/html\nContent-Length: "+std::to_string(getFileSize(getErrorFileName(client,"405")))+"\r\n\r\n",getErrorFileName(client, "405"), client);
		return ;
	}
}

		//-------------------------------------------------------------------------------------------
void parseRequest::display_request(parseRequest parse)
{
	std::map<std::string, std::string>::iterator it = parse._data.begin();
					// showning results by iterating inside map container
		while (it != parse._data.end())
 		{
			std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
			++it;
 		}
		// std::cout << "-----------------body----------------------\n";
		// // std::cout <<  parse._body << std::endl;
		// std::cout << "-----------------body----------------------\n";
}

std::string getErrorFileName(Client &client ,std::string code) {
	std::string fileName;

	std::vector<std::string>::iterator it = client.location.error_cods.begin();
	std::vector<std::string>::iterator it1 = client.location.files_path.begin();

	while (it != client.location.error_cods.end()) {
		if (*it == code) {
			fileName = *it1;
			std::cout << "fileName = " << fileName << std::endl;
			return fileName;
		}
		it++;
		it1++;
	}
	std::string _default;
	_default = code.append("page.html");
	std::cout << "default = " << _default << std::endl;
	return _default;

}

void	parseRequest::check_request(Server &server,Client &iter) {
	if (!iter.checker) {
		// printf("here\n");
		if (this->_data["method"] == "POST") {
			if (this->_data["Content-Length"].length() == 1){
				server.write_in_socket_client("HTTP/1.1 400 KO\nContent-Type: text/html\nContent-Length: "+std::to_string(getFileSize(getErrorFileName(iter,"400")))+"\r\n\r\n",getErrorFileName(iter, "400"), iter);
				return ;
			}
		}

		int _check_url = check_url(this->_data["path"]);
		if (_check_url) {
			server.write_in_socket_client("HTTP/1.1 400 KO\nContent-Type: text/html\nContent-Length: "+std::to_string(getFileSize(getErrorFileName(iter,"400")))+"\r\n\r\n",getErrorFileName(iter, "400"), iter);
			return;
		}

		int _check_url_size = check_url_size(this->_data["path"]);
		if (_check_url_size) {
			server.write_in_socket_client("HTTP/1.1 414 KO\nContent-Type: text/html\nContent-Length: "+std::to_string(getFileSize(getErrorFileName(iter,"414")))+"\r\n\r\n",getErrorFileName(iter, "414"), iter);
			return ;
		}

		int _check_matched_location = matched_location(server ,this->_data["path"],iter);
		if (_check_matched_location == -1) {
    		server.write_in_socket_client("HTTP/1.1 404 KO\nContent-Type: text/html\nContent-Length: "+std::to_string(getFileSize(getErrorFileName(iter,"404")))+"\r\n\r\n",getErrorFileName(iter, "404"), iter);
			return ;
		}
		if ((size_t)std::atoi(this->_data["Content-Length"].c_str()) > server.body_size){
			//std::cout << "body size = " << std::atoi(iter.location.body_size.c_str()) << std::endl; 
			server.write_in_socket_client("HTTP/1.1 413 KO\nContent-Type: text/html\nContent-Length: "+std::to_string(getFileSize(getErrorFileName(iter,"413")))+ "\r\n\r\n",getErrorFileName(iter, "413"), iter);
			return ;
		}
		// if (!iter.location.redirec.empty()) {
		// 	std::cout << "redirec = " << iter.location.redirec << std::endl;
		// 	// server.write_in_socket_client("HTTP/1.1 413 KO\nContent-Type: text/html\nContent-Length: 220\r\n\r\n","413error.html", iter);
		// 	server.write_in_socket_client("HTTP/1.1 301 MOVED PERMANENTLY\nLocation: " + iter.location.redirec + "\nContent-Type: text/html\nContent-Length: 200\r\n\r\n", getErrorFileName(iter, "301"), iter);
		// 	return ;
		// }
		iter.checker = true;
	}
	check_methods(server, iter);
}


std::map<std::string, std::string> parseRequest::getData()
{
	return this->_data;
}
