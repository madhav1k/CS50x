#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start_size, end_size, n, y;
    // TODO: Prompt for start size
    do
    {
        start_size = get_int("Enter start size:");
    }
    while (start_size < 9);
    // TODO: Prompt for end size
    do
    {
        end_size = get_int("Enter end size:");
    }
    while (end_size < start_size);
    // TODO: Calculate number of years until we reach threshold
    y = 0;
    n = start_size;
    for (y = 0; n < end_size; y++)
    {
        n = n + (n / 3) - (n / 4);
    }
    // TODO: Print number of years
    printf("Years: %i\n", y);
}
