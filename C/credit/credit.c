#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long tipe = 0; //To show which kind of card this is, if valid.
    long sum = 0; // to make the sum of the non multiplied numbers
    long mult = 0; // to make the sum of the multipled numbers
    long card = get_long("Card numer ? "); // asking the card's number
    int x = 0; // to count how many numbers are in the card
    while (card >= 1) // while the total card number, being divided by 10, isn't lower than 1
    {
        x++; // counting numbers of digits
        if (x % 2 == 0) // if the number is odd, thus is a other number starting from second last
            {
            mult = mult + (((2 * ( card % 10)) / 10) % 10) + ( 2 * (card % 10) % 10) ;
             // multply it by two than some the first and last digit of it to the mult sum
            }
        else // if it's not a number to be multiplied
            {
            sum = sum + card % 10; // sums it to the sum of numbers that aren't multiplied

            }
        card = card / 10; //removes the used number and continues

        if (card == 34 || card == 37) {tipe = 1;} // if the first two digitas are 34 or 37, it's a AMEX card
        if (card >= 51 && card <= 55) {tipe = 2;}// if the first two digitas are between 51 and 55, it's a MASTERCARD
        if (card == 4 ) { tipe = 3;}// if the first digit is 4, it's a Visa card
    }
    long total = sum + mult; //summing the sum of the multiplied and non multipled
    int lastdig = total % 10; // seeing if the last digit of the sum is 0
    if(lastdig == 0 && x == 15 && tipe == 1)
        {printf("AMEX\n");} // seeing if the card is valid and AMEX
    else if(lastdig == 0 && x == 16 && tipe == 2)
        {printf("MASTERCARD\n");}// seeing if the card is valid and MASTERCARD
    else if(lastdig == 0 && x == 13 && tipe == 3)
        {printf("VISA\n");}// seeing if the card is valid and VISA
    else if(lastdig == 0 && x== 16 && tipe == 3)
        {printf("VISA\n");}// seeing if the card is valid and VISA
    else {printf("INVALID\n");}// if it's not one of the above, it's INVALID
}