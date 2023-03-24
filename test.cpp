#include <iostream>
#include <string>
#include <filesystem>
int main(int ac, char **av)
{
    std::filesystem::path path = "/Users/orbiay/Desktop/Webserv_v2";
    if (std::filesystem::is_directory(path)) {
        std::cout << path << " is a directory\n";
    }
    else if (std::filesystem::is_regular_file(path)) {
        std::cout << path << " is a file\n";
    }
    else {
        std::cout << path << " is neither a directory nor a file\n";
    }
}