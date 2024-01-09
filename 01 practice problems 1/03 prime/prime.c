// Find prime or not
// Print all prime numbers in the given range

#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    for (int x = 2; x < number; x++)
    {
        // If there is a factor other than 1 and
        // itself of number then number is not prime
        if (number % x == 0)
        {
            return false;
        }
    }
    return true;
}
