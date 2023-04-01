#include <iostream>
#include <fstream>

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

int main() {
    // Open the file in read mode
    int fd = open("./www/serve.html", O_RDWR);
    
    // Read the file contents into a string variable
    char *str = (char *)malloc(sizeof(char *) * 2000);
    memset(str, 0, 2000);
    read(fd, str, 1999);

    std::cout << str << std::endl;

    // Close the file
    
    // Search for the string you want to replace
    std::string content = str;
    string searchString = "<ul>";
    size_t pos = content.find(searchString);
    content.insert(pos + 4,"\nHI");
    write(fd,content.c_str(),content.length());
    std::cout<<content<<std::endl;
    // Open the file in write mode and seek to the position where you want to write
    //ofstream outFile("./www/serve.html", ios::out);
    //outFile.seekp(pos);
    
    // Write the new string at the desired position
    //string newString = "Hi";
    
    // Close the file
    
    return 0;
}

