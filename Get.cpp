#include"response.hpp"

std::string get_html_file(std::string& links)
{
	int fd = open("./www/serve.html", O_RDWR);
    char *str = (char *)malloc(sizeof(char *) * 2000);
    memset(str, 0, 2000);
    read(fd, str, 1999);
    std::string content = str;
    std::string searchString = "<ul>";
    size_t pos = content.find(searchString);
    content.insert(pos + 4,links);
	return (content);
}

void addslash(std::string &root)
{
	if (*(root.end() - 1) != '/')
		root += "/";
}
std::string link_maker(std::string &root,std::string name)
{
    (void)root;
	std::string link = "      <li><a href=\"" + name + "\">" + name + "</a></li>\n";
	return (link);
}
void Response::autoindex_mode(std::string &auto_index,std::string &default_index,std::string root,Server &server)
{
	(void)server;
	std::string links;
	if (auto_index == "on" && default_index.empty())
	{
		DIR *Directory;
		Directory = opendir(root.c_str());
		if (Directory != NULL)
		{
			std::cout<<"HOLALALALAL"<<std::endl;
			struct dirent *info = readdir(Directory);
			while(info != NULL)
			{
				links += link_maker(root,info-> d_name);
				info = readdir(Directory);
			}
			std::string body = get_html_file(links);
			std::string header = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " + std::to_string(body.length()) + "\r\nConnection: closed\r\n\r\n";
			header += body; 
			write(client.fd_client,header.c_str(),header.length());
            std::cout<<body<<std::endl;
			client.is_delete = true;
		}
	}
}

void Response::Get(Server &server) {
	// (void)server;
	std::string root = "." + client.parse._data["path"];
	client.extension = client.parse._data["path"];
    std::string content_type = getContentType(server);
	std::ifstream infile(root.c_str());
	std::string header;
	std::string auto_index = "on";
	std::string default_index;
	if (!infile.good())
	{
		header = "HTTP/1.1 404 not found\nContent-Type: " + content_type + "\nContent-Length: 213r\r\nConnection: closed\r\n\r\n";
		server.write_in_socket_client(header,"404error.html", client);
	}
	else
	{
		infile.close();
		if (is_directory_or_file(root) == FILE)
		{
			size_file(root);
			std::cout<<content_type<<std::endl;
			header = "HTTP/1.1 200 OK\nContent-Type: " + content_type + "\nContent-Length:" + client.sizefile + "\r\nConnection: closed\r\n\r\n";
			server.write_in_socket_client(header,root,client);
		}
		else if (is_directory_or_file(root) == DIRE)
		{
			addslash(root);
			std::cout<<root<<std::endl;
			if (auto_index == "on" && default_index.empty())
			{
				autoindex_mode(auto_index,default_index,root,server);
			}
			else if (!default_index.empty())
			{
				size_file(root + default_index);
				client.extension = default_index;
				std::cout<<client.extension<<std::endl;
				header = "HTTP/1.1 200 OK\nContent-Type:  "+ getContentType(server) +"\nContent-Length: " + client.sizefile + "\r\nConnection: 	closed\r\n\r\n";
				server.write_in_socket_client(header,root + default_index , client);
			}
			else if (auto_index.empty() || auto_index == "off")
			{
				header = "HTTP/1.1 403 Forbidden\nContent-Type:text/html\nContent-Length: 	169\r\nConnection: closed\r\n\r\n";
				server.write_in_socket_client(header,"403error.html", client);
			}
		}
	}
}