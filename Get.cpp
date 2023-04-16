#include"response.hpp"
#include"CGI.hpp"
std::string get_html_file(std::string& links)
{
	int fd = open("./www/serve.html", O_RDWR);
	if(fd == -1)
		return "error";
    char *str = (char *)malloc(sizeof(char *) * 2000);
    memset(str, 0, 2000);
    read(fd, str, 1999);
    std::string content = str;
    std::string searchString = "<ul>";
    size_t pos = content.find(searchString);
    content.insert(pos + 4,links);
	close(fd);
	return (content);
}

void addslash(std::string &root)
{
	if (*(root.end() - 1) != '/')
		root += "/";
}
std::string link_maker(std::string &path,std::string name)
{
	std::string link = "      <li><a href=\"/" + path + "\">" + name + "</a></li>\n";
	return (link);
}
void Response::autoindex_mode(bool &auto_index,std::string &default_index,std::string root,Server &server,Client &client)
{
	(void)server;
	std::string links;
	if (auto_index == true && default_index.empty())
	{
		DIR *Directory;
		Directory = opendir(root.c_str());
		if (Directory != NULL)
		{
			struct dirent *info = readdir(Directory);
			while(info != NULL)
			{
				links += link_maker(client.path,info-> d_name);
				info = readdir(Directory);
			}
			//std::cout<<"HOLALALALAL"<<std::endl;
			std::string body = get_html_file(links);
			if (body == "error")
			{
				client.is_delete = true;
				return;
			}
			std::string header = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " + std::to_string(body.length()) + "\r\nConnection: closed\r\n\r\n";
			header += body; 
			write(client.fd_client,header.c_str(),header.length());
			client.is_delete = true;
		}
	}
}
void init_vars(std::string &root,bool &auto_index,std::string &default_index,Server &server,Client &client)
{
	(void)server;
	(void)default_index;
	(void)client;
	root = client.location.root_val;
	client.path = root + client.location.location_val;
	addslash(root);
	auto_index = client.location.autoindex;
	default_index = client.location.index_val;
}

void Response::file_handler(Server &server)
{
	if (is_directory_or_file(client.path) == FILE)
	{
		//CGI c;
		//c.cgi(server.server_config,client);
		size_file(client.path);
		client.header = "HTTP/1.1 200 OK\nContent-Type: " + client.content_type + "\nContent-Length:" + client.sizefile + "\r\nConnection: //closed\r\n\r\n";
		server.write_in_socket_client(client.header,client.path,client);
	}
	else
		return;
}

bool Response::check_if_exist(Server &server)
{
	std::ifstream infile(client.path + client.location.index_val);
	if (!infile.good())
	{
		infile.close();
		size_file(getErrorFileName(this->client ,"404"));
		client.extension = "404error.html";
		client.content_type = getContentType(server);
		client.client_header = "HTTP/1.1 404 not found\nContent-Type: " + client.content_type + "\nContent-Length: "+ client.sizefile +"\r\nConnection: closed\r\n\r\n";
		server.write_in_socket_client(client.client_header,getErrorFileName(this->client ,"404"), client);
		return false;
	}
	infile.close();
	return true;
}

void Response::directory_handler(Server &server)
{
	std::string default_index;
	std::string root;
	bool auto_index;
	init_vars(root,auto_index,default_index,server,client);
	if (is_directory_or_file(client.path) == DIRE)
	{
		addslash(client.path);
		if (auto_index == true && default_index.empty())
			autoindex_mode(auto_index,default_index,client.path,server,client);
		else if (!default_index.empty())
		{
			if (check_if_exist(server))
			{
				size_file(client.path + default_index);
				std::cout<<"hola"<<std::endl;
				client.extension = default_index;
				client.client_header = "HTTP/1.1 200 OK\nContent-Type:  "+ getContentType(server) +"\nContent-Length: " + client.sizefile + "\r\nConnection: 	closed\r\n\r\n";
				server.write_in_socket_client(client.client_header,client.path + default_index , client);
			}
		}
		else if (auto_index == false)
		{
			client.client_header = "HTTP/1.1 403 Forbidden\nContent-Type:text/html\nContent-Length:"+std::to_string(getFileSize(getErrorFileName(client,"400")))+ "\r\nConnection: closed\r\n\r\n";
			server.write_in_socket_client(client.client_header,getErrorFileName(client, "403"), client);
		}
	}
	else
		return;
}




void Response::Get(Server &server) {

	std::string root = client.location.root_val;
	addslash(root);
	client.path = root + client.location.location_val;
	client.extension = client.location.location_val;
    client.content_type = getContentType(server);
	std::ifstream infile(client.path);
	//addslash(root);
	if (!infile.good())
	{
		size_file(getErrorFileName(client, "404"));
		client.extension = "404error.html";
		client.content_type = getContentType(server);
		
		client.client_header = "HTTP/1.1 404 not found\nContent-Type: " + client.content_type + "\nContent-Length: "+ client.sizefile +"\r\nConnection: closed\r\n\r\n";
		server.write_in_socket_client(client.client_header,getErrorFileName(client, "404"), client);
	}
	else
	{
		infile.close();
		//std::cout<<client.path<<std::endl;
		/**************************************************************/
		// 	IF URL THAT THE CLINET SENT ME IS A FILE EXAMPLE :         /
		//		    http://localhost:8080/index.html				   /
		/**************************************************************/
		file_handler(server);
		/**************************************************************/
		//	IF URL THAT THE CLIENT SENT ME IS DIRECTORY LIKE:          /           
		//		           http://localhost:8080/                      /
		/**************************************************************/
		directory_handler(server);
	}
}
