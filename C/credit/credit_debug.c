#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long tipe = 0;

    long sum = 0;
    long mult=0;
    long card = get_long("Card numer ? ");
    int x = 0;
    while (card >= 1)
    {
        x++;
            if (x%2==0)
                {
                mult = mult + (((2*(card%10))/10)%10) + (2*(card%10)%10) ;
                printf("first mult %li\n",(((2*(card%10))/10)%10));
                printf("second mult %li\n",(2*(card%10)%10));
                printf("x = %i\n",x);
                }
            else
                {
                sum = sum + card%10;
                printf("sum %li\n",card%10);
                printf("x = %i\n",x);
                }
        card = card/10;

        if (card == 34 || card == 37) {tipe = 1;}
        if (card >= 51 && card <= 55) {tipe = 2;}
        if (card == 4 ) { tipe = 3;}
    }
    long total = sum + mult;
    int lastdig = total%10;
    lastdig++;
    lastdig--;
    printf("last digit of the sum = %i\n",lastdig);
    printf("tipe = %li\n",tipe);
    if(lastdig == 0){printf("ok1\n");}
    if(x == 13){printf("ok2\n");}
    if(tipe == 3){printf("ok3\n");}
    if(lastdig == 0 && x== 15 && tipe == 1 ){printf("AMEX\n");}
    else if(lastdig == 0 && x== 16 && tipe == 2 ){printf("MASTERCARD\n");}
    else if(lastdig == 0 && x== 13 && tipe == 3 ){printf("VISA\n");}
    else if(lastdig == 0 && x== 16 && tipe == 3 ){printf("VISA\n");}
    else {printf("INVALID\n");}


}