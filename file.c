#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>
int calucul_digit(char *av)
{
    int len = strlen(av);
    int count = 0;
    for(int i =0;i < len;i++)
        if (isdigit(av[i]))
            count++;
    return (count);
}

void check_error(char *str){
    if ((int)strlen(str) % 2 != 0)
    {
        printf("error : something wrong.");
        exit(1);
    }
}

int main(int ac, char **av)
{
    if (ac > 1)
    {
        int len  = strlen(av[1]);
        char *str  = malloc(sizeof(char *) * calucul_digit(av[1]));
        int j = 0;
        for(int i = 0; i < len;i++)
        {
            if (isdigit(av[1][i]))
            {
                str[j] = av[1][i];
                j++;
            }
        }
        check_error(str);
        len = strlen(str);
        printf("(%c,%c)",str[0],str[1]);
        char c = str[1];
        for(int i = 1;i < len; i += 2)
        {
            if (str[i + 1] && str[i + 2])
            {
                if (c < str[i + 1] && str[i + 2] > c)
                {
                    printf("(%c,%c)",str[i + 1],str[i + 2]);
                    c = str[i + 2];
                }
            }
        }
    }
}