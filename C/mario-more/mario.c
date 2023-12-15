#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int number;

    do//to keep making the same question till the number satisfy the condition to leave the while
    number = get_int("give me a number between 1 and 8 ");
    while (number < 1||number > 8);
    // initial condition, to keep repeating the commands till N equals the number given
    for (int n = 1; n <= number; n++)
    {
    // in order to keep the blocks aligned, i make it print spaces for the difference between curent N and the number given
        for (int m = 1; m <= number - n; m++) {printf(" ");}
    // for inside a for, to make the blocks ranging from 1 to 8 till it reaches the present value of N
        for (int m = 1; m <= n; m++) {printf("#");}
    //to print the space between the two blocks
        printf("  ");
    // same as before, but on the other side
        for (int m = 1; m <= n; m++) {printf("#");}
    // to jump a line at the end of the code
        printf("\n");
    }
}