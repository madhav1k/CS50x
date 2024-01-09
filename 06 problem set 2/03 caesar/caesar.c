#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int rotate(char c, int k);

int main(int argc, string argv[])
{
    // check commandline argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int k = 0; k < strlen(argv[1]); k++)
    {
        if (isalpha(argv[1][k]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int k = atoi(argv[1]) % 26;
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (!isalpha(plaintext[i]))
        {
            printf("%c", (plaintext[i]));
            continue;
        }
        printf("%c", rotate(plaintext[i], k));
    }
    printf("\n");
    return 0;
}

int rotate(char c, int k) //rotate char k positions
{
    int ascii_offset = isupper(c) ? 65 : 97;
    int p_i = c - ascii_offset;
    int c_i = (p_i + k) % 26;
    return c_i + ascii_offset;
}