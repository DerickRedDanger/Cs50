#include <stdio.h>
#include <cs50.h>
int x = 0; // counting how many times the function coll was used till reaching n == 1, ignoring when N =1
int coll( int n); // calling the function so the program know it exists

int main(void)
{
coll (7); // using the function with using 7 as N
printf("%i\n",x); // printing how many times the function was used

}

int coll (int n) // the function it self.
{
    if (n == 1) // if n == 1, return 1
    {return 1;}
    else if (n % 2 != 0) // if n is odd, return coll with 3n+1
    {
        x++;
        return coll(3*n +1);
    }
    else if (n % 2 == 0) // if n is even, return coll with n/2
    {
        x++;
        return coll(n / 2);
        }
    else // since a non void function has to return something on all of it's paths
    {
        return 0;
        printf("something went wrong")
    }
}