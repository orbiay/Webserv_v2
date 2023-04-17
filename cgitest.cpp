#include<iostream>
#include<fstream>
#include<fcntl.h>
#include<unistd.h>
int main ()
{
    std::string path = "/Users/orbiay/Desktop/web/test.php";
    std::cout<<path.substr(path.rfind(".") + 1, path.length())<<std::endl;
    int fd =  open("./rand" ,'r');
    char *s = new char[794];
    memset(s,0,794);
    int size = read(fd,s,793);
    std::string str = s;
    size_t pos = str.find("\r\n\r\n");
    if (pos != std::string::npos) {
        std::string header = str.substr(0, pos);
        std::string body = str.substr(pos + 4);
        std::cout << "Header:\n" << header << std::endl;
        std::cout << "Body:\n" << body << std::endl;
    }
}