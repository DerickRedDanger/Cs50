#include <stdio.h> //Including Studio's library
#include <cs50.h>  //Including Cs 50 library
int main(void)
{
    string name = get_string("what's your name? ");
    // Command to get a string (phrase) and putting it's value inside "name" while also asking a question.
    printf("hello, %s\n", name);
    // command to print hello "name", the %s is a place holder for a string, which value becomes the value in name. /n is to jump the $ to the next line
}