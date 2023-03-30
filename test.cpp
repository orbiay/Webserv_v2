#include <iostream>
#include <fstream>

int main() {
    std::ifstream file("test.cpp", std::ifstream::ate | std::ifstream::binary);
    if (file.is_open()) {
        std::streamsize size = file.tellg();
        std::cout << "File size is: " << size << " bytes." << std::endl;
    }
    else {
        std::cout << "Unable to open file." << std::endl;
    }
    return 0;
}
