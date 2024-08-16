#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string key;
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    key = argv[1];

    // converting key to uppercase
    for (int i = 0; i < strlen(key); i++)
    {
        key[i] = toupper(key[i]);
    }

    // checking if key has only letters
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain letters.\n");
            return 1;
        }
    }

    // checking for 26 characters
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // checking for unique characters
    for (char currentChar = 'A'; currentChar <= 'Z'; currentChar++)
    {
        int letterCount = 0;
        for (int i = 0; i <= strlen(key); i++)
        {
            if (currentChar == key[i])
            {
                letterCount++;
                if (letterCount > 1)
                {
                    printf("Key must contain each letter only once.\n");
                    return 1;
                }
            }
        }
    }

    string plaintext = get_string("plaintext: ");
    string ciphertext = plaintext;

    // printing ciphertext
    for (int i = 0; i < strlen(ciphertext); i++)
    {
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = key[plaintext[i] - 65];
        }
        if (islower(plaintext[i]))
        {
            ciphertext[i] = key[plaintext[i] - 97];
            ciphertext[i] = tolower(ciphertext[i]);
        }
    }
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}