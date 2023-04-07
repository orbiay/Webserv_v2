#include <iostream>
#include <fstream>
#include <string>
#include<fcntl.h>
#include<unistd.h>


int main() {
    int file = open("fcc", O_CREAT | O_RDWR, 0644);
    int i = 1;
    while (i)
    {
        char c;
        i += read(file, &c,1);
        write(1,&c,1);
    }
}
    
