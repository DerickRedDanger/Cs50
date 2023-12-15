#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

//defining BYTE to use a the size for reading and writting
typedef uint8_t BYTE;

// Since we only need to read 512 bytes at a time and not one by on
//i se the block size to 512 bytes
int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{

    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // Remember filenames
    char *infile = argv[1];
    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }
    int n = 0; // variale to name the file
    char *filename = malloc(10 * sizeof(char));// saving space to name the file
    // possibly could've done it with just a array of char (char filename[10])
    sprintf(filename, "%03i.jpg", n); //naming the file
    FILE *outptr = fopen(filename, "w");// opening the file
    n = -1;// set to -1 for the purpose of making the first if trigger only once

    int p = 0;
    BYTE Buffer[512];
    while (fread(Buffer, sizeof(BYTE), BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        if(n == -1 && Buffer[0] == 0xff && Buffer[1] == 0xd8 && Buffer[2] == 0xff && (Buffer[3] & 0xf0) == 0Xe0) // Buffer[3] >= 0Xe0 && Buffer[3] <= 0Xef
        {
            n = 0;
            if (outptr == NULL)
            {
                 fclose(inptr);
                printf("Could not create %s.\n", filename);
                return 1;
            }
            fwrite(Buffer, sizeof(BYTE), BLOCK_SIZE, outptr);
        }
        else if (n >=0  && Buffer[0] == 0xff && Buffer[1] == 0xd8 && Buffer[2] == 0xff && (Buffer[3] & 0xf0) == 0Xe0 ) //(Buffer[3] && 0xf0)== 0Xe0
        {
            fclose(outptr);
            n++;
            p = n;
            printf("%i\n",n);
            sprintf(filename, "%03i.jpg", n);
            printf("%i\n",n);
            n = p;
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                printf("Could not create %s\n", filename);
                return 1;
            }
            fwrite(Buffer, sizeof(BYTE), BLOCK_SIZE, outptr);
        }
        else if (n >=0)
        {
            fwrite(Buffer, sizeof(BYTE), BLOCK_SIZE, outptr);
        }
    }
    fclose(outptr);
    fclose(inptr);
    free(filename);
}
