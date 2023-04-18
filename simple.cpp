#include <iostream>

int main() {
    // Set the content type to HTML
    std::cout << "Content-type: text/html\r\n\r\n";
    std::cout << "<html><head><title>Hello, World!</title></head><body>";
    std::cout << "<h1>Hello, World!</h1>";
    std::cout << "</body></html>";

    return 0;
}
