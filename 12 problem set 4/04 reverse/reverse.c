#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("File not found.\n");
        fclose(inptr);
        return 2;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) != 0)
    {
        fclose(inptr);
        return 3;
    }

    // Open output file for writing
    // TODO #5
    FILE *outptr = fopen(argv[2], "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        return 4;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    // TODO #7
    int size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[size];
    fseek(inptr, -size, SEEK_END);
    while (ftell(inptr) >= sizeof(header))
    {
        fread(&buffer, size, 1, inptr);
        fwrite(&buffer, size, 1, outptr);
        fseek(inptr, -(size * 2), SEEK_CUR);
    }
    fclose(inptr);
    fclose(outptr);
    return 0;
}

int check_format(WAVHEADER header)
{
    // TODO #4
    char wave[] = {'W', 'A', 'V', 'E'};
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != wave[i])
        {
            printf("Not a valid WAV file!\n");
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * (header.bitsPerSample / 8);
}