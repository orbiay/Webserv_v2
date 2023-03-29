#include <iostream>
#include <string>
#include <sys/stat.h>

int main() {
    const char* path = "./server.hpp";
    struct stat file_stat;

    // Get information about the file or directory
    if (stat(path, &file_stat) != 0) {
        std::cerr << "Error getting file/directory informaion\n";
        return 1;
    }

    // Check if it's a directory
    if (S_ISDIR(file_stat.st_mode)) {
        std::cout << path << " is a directory\n";
    }
    // Check if it's a regular file
    else if (S_ISREG(file_stat.st_mode)) {
        std::cout << path << " is a regular file\n";
    }
    // Something else
    else {
        std::cout << path << " is not a directory or regular file\n";
    }

    return 0;
}

