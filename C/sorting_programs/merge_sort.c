#include <stdio.h>
#include <cs50.h>

int b = 0;
void merge_sort(int n[], int start, int end, bool decreasing, int number);
// calling the function so the program know about it.
//first it's the array it has to sort,
//second if you want it sorted increasing or decreasing

int main (void)
{

    int n[] = {1,2,3,5,4,6,7,8,10,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    int m[] = {1,2,3,5,4,6,7,8,10,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    int o[] = {1,2,3,5,4,6,7,8,10,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    int c = -1; // Watch it ! here we need C to start at -1
    while(n[c] !='\0' )
    {
        c++;
    }

    merge_sort(n,0,c,false,0);// using the function while increasing

    for( int x = 0; x < c; x++)
    printf("%d\n",n[x]); // printing the sorted array
}

void merge_sort(int n[], int start, int end, bool decreasing, int number)
{
    int x = start;
    int y = end/2;
    int z = end/2;
    int j = start;
    int k = end;
    int m[1];
    int o[1];
       for (int g = 0; g <= k; g++)
            {
                m[g] = n[g];
                o[g] = n[g];
            }


if (end - start > 1 )
{
    merge_sort(n,start,end/2,decreasing, number + 1);
    merge_sort(n,end/2,end,decreasing, number + 1);
}

if (number%2 == 0)
{
    while (j <= k)
    {
        if (m[x] >= m[y] && x < z)
        {
            o[j] = m[x];
            x++;
            j++;
        }
        if (m[y] > m[x] && y < k)
        {
            o[j] = m[y];
            j++;
            y++;
        }
    }
}
else if (number%2 != 0)
{
    while (j <= k)
    {
        if (o[x] >= o[y] && x < z)
        {
            m[j] = o[x];
            x++;
            j++;
        }
        if (o[y] > o[x] && y < k)
        {
            m[j] = o[y];
            j++;
            y++;
        }
    }
}

if (number == 0)
{
        if (decreasing)
{
    for( int q = 0; q > end; q++)
    n[q] = o[end - q];
}
    else
    {
    n = o;

}}

}