#include <stdio.h>

int main(int argc, char *argv[])
{
    char ch;
    while ((ch=fgetc(ptr))!=EOF)
        printf("%c",ch);
}