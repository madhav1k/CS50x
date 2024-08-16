#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 2;
    }
    FILE *outptr = NULL;
    BYTE buffer[512];
    int jpeg = 0;
    char filename[8];
    while (fread(buffer, 1, 512, inptr) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (outptr != NULL)
            {
                fclose(outptr);
            }
            sprintf(filename, "%03d.jpg", jpeg);
            jpeg++;
            outptr = fopen(filename, "w");
        }
        if (outptr != NULL)
        {
            fwrite(buffer, 1, 512, outptr);
        }
    }
    fclose(inptr);
    if (outptr != NULL)
    {
        fclose(outptr);
    }
    return 0;
}