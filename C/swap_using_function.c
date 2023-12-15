#include <stdio.h> //Including Studio's library

void swap (int *a, int *b);
int x = 1;
int y = 2;

int main(void)
{
    printf("x is %i, y is %i\n", x,y);
    swap(&x,&y);
    printf("x is %i, y is %i\n", x,y);
}

void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}