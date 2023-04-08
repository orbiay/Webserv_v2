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

int main() {
   int fd = open (".f", O_CREAT | O_RDWR );
   char *str = new char[1024];
   int i = read(fd,str,1024);
   str[i] = 0;
   std::cout<<str;
    return 0;
}

