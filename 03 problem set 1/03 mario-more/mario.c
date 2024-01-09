#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int num;
    do
    {
        num = get_int("Height: "); // input height
    }
    while (num < 1 || num > 8);

    for (int hash = 1; hash <= num; hash++)
    {
        for (int i = 1; i <= num - hash; i++)
        {
            printf(" ");
        }

        for (int j = 1; j <= hash; j++)
        {
            printf("#");
        }

        printf("  ");

        for (int j = 1; j <= hash; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}