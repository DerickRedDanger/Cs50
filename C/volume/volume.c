// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE]; //setting the size of the headers to 1 byte (8 bits)
    fread(header, HEADER_SIZE, 1, input); // reading and copying header_size bytes (44)
    fwrite(header, HEADER_SIZE, 1, output);// writting header_size bytes

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer; //setting the size of the headers to 2 byte (16 bits)
    while (fread(&buffer, sizeof(int16_t), 1, input)) // reading and copying 2 byte (16 bits), up till the end of the file
    {
        buffer = buffer * factor; // multplying the buffer value by the factor
        fwrite(&buffer, sizeof(int16_t), 1, output);// writting the new buffer in the output
    }

    // Close files
    fclose(input);
    fclose(output);
}
