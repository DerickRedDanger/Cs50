#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    string key = argv[1]; // defining Key as equal to the input, so i can work with each of it's letters.
    int l = strlen(key); // seeing how many characters are in the input
//Validation
    if (argv[1] == NULL) // if the input doesn't have a command, return 1
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (argv[2] != NULL)// if the input has more than a command, return 1
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (l != 26)// if the input doesn't have 26 characters, return 1
    {
        printf("the key Must be 26 characters long\n");
        return 1;
    }
    for (int z = 0; z < l ; z++)// checking if the input doesn't have repeated characters
    {
        if (isupper(key[z])|| islower(key[z])) // seeing if they are in lower or upper case, if they are neither than they aren't a alphabet character
        {
            for (int c = 0 ; c < l; c++)
            {
                if (z != c)
                {
                    if (tolower(key[z]) == tolower(key[c]))// forcing to lowercase, then comparing each caracter to see if they are repeated
                    {
                        printf("Key must not contain repeated characters\n");// if one are, return 1
                        return 1;
                    }
                }
            }
        }
        else// in case some character aren't upper nor lower, than they aren't alphabetic, return 1
        {
            printf("the key must only contain alphabetic characters\n");
            return 1;
        }
    }
//turning Plaintext into cyphertext
    char cypher[26];// creating the char that will be used to change the plaintext
    for (int i = 0; i < 26; i++)
    {
        if (isupper(key[i]))// if the char is upper, than reduce (65+i) from it. since it's A(65) B(66) CD...
        {
            cypher[i] = (key[i]) - 65 - i;
        }
        else // if the char isn't upper, than reduce (97+i) from it. since it's a(97) b(98) cd...
        {
            cypher[i] = key[i] - 97 - i;
        }
    }
    string plaintext = get_string("plaintext ");// getting the plain text
    char ciphertext[strlen(plaintext)];// adjusting the ciphertext array to be as long as the plain one
    for (int x = 0, y = strlen(plaintext); x < y; x++)
    {
        if (isupper(plaintext[x]) || islower(plaintext[x])) // if the plain text is a alphabetic character, than add the cipher to it.
            for (int a = 0; a < 26; a++)
            {
                if (plaintext[x] == 65 + a || plaintext[x] == 97 + a) // comparing to the upper or lower alphabet than replacing it
                    ciphertext[x] = plaintext[x] + cypher[a];
            }
        else // if the plain text isn't a alphabetic character, just copy it
        {
            ciphertext[x] = plaintext[x];
        }
    }
    printf("ciphertext: ");
    for (int u = 0; u < strlen(plaintext); u++) // printing the new plaintext
        {printf("%c", ciphertext[u]);}
    printf("\n"); //jumping a line
    return 0;
}