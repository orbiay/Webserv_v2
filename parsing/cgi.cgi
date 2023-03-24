/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomman <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:09:34 by aomman            #+#    #+#             */
/*   Updated: 2023/03/24 01:09:36 by aomman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<iostream>

void send_CGI_header(){
    std::cout << "Content-type: text/html\n";
    std::cout << "\n"; // this blank line is a necessary part of the CGI protocol.
}
void send_contents()
{
	std::cout << "<!doctype html>\n";
	std::cout << "<html>\n";
	std::cout << "<title>Hello</title>\n";
	std::cout << "<p>Hello, world!\n";
    // C strings can, with care, contain double-quote characters, newlines, etc.
	std::cout << "<p><a href=\"http://validator.w3.org/check?uri=referer\">";
	std::cout << "Valid.</a>\n";
	std::cout << "</html>\n";
	std::cout << std::endl;
}

int main(){
    send_CGI_header();
    send_contents();
    return 0;
}
