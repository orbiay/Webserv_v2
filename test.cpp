#include <iostream>
#include <fstream>
#include <string>
#include<fcntl.h>
#include<unistd.h>


#include <stdio.h>
#include <dirent.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


using namespace std;

#include <iostream>
#include <string>

int main() {
    std::string str = "Hello, world!";
    std::string subStr = "world";

    size_t found = str.find(subStr);

    if (found != std::string::npos) {
        std::cout << "Substring found at position " << found << std::endl;
    } else {
        std::cout << "Substring not found" << std::endl;
    }

    return 0;
}
