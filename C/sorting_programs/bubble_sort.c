#include <stdio.h>
#include <cs50.h>

int bubble_sort(int n[], bool decreasing);
// calling the function so the program know about it.
//first it's the array it has to sort,
//second if you want it sorted increasing or decreasing

int main (void)
{

    int n[]={1,2,3,5,4,6,7,8,10,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
    int c = 0;
    while(n[c] !='\0' )
    {
        c++;
    }
    bubble_sort(n,false);// using the function while increasing

    for( int x = 0; x < c; x++)
    printf("%d\n",n[x]); // printing the sorted array
}



int bubble_sort(int n[], bool decreasing)
{
    int z; // used to save the values of the array before swapping them
    int c = 0; // using to find out how long the array is
    int k = 10;
    while(n[c] !='\0' )
    {
        c++;
    }

    if (decreasing)
    {
        while (k!=0)
        {
            k = 0;
        for ( int x = 0; x < c-1; x++)
        {
                if (n[x] < n[x+1])
                {
                    printf("nx %i\n",n[x]);
                    printf("nx+1 %i\n",n[x+1]);
                    printf("z %i\n",z);
                    z = n[x];
                    n[x] = n[x+1];
                    n[x+1] = z;
                    k++;
                    printf("nnx %i\n",n[x]);
                    printf("nnx+1 %i\n",n[x+1]);
                    printf("z %i\n",z);
                }
            }
        c--;
        }

    }
    else
   {
        while (k!=0)
        {
            k = 0;
        for ( int x = 0; x < c-1; x++)
        {
                if (n[x] > n[x+1])
                {
                    z = n[x];
                    n[x] = n[x+1];
                    n[x+1] = z;
                    k++;;
                }
            }
        c--;
        }
    }
        return 'n';
}