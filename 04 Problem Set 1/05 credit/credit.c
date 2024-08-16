#include <cs50.h>
#include <math.h>
#include <stdio.h>

long long cardNumber = 0;

int main(void)
{
    do
    {
        cardNumber = get_long_long("Number: ");
    }
    while (cardNumber <= 0);

    long long cardLength = floor(log10(cardNumber)) + 1;

    long long cardDigits[cardLength];

    // create an array of long long (still unsure why array needs to be long long) and fill with the cardNumber digits
    for (int i = (cardLength - 1); i >= 0; i--)
    {
        cardDigits[i] = cardNumber % 10;
        cardNumber = floor(cardNumber / 10);
    }

    // implement Luhn's algorithm first

    // multiply every other digit starting at second-to-last by two and store in an array
    long long doubleDigit[cardLength / 2];

    for (int i = (cardLength - 2), ii = 0; i >= 0; i -= 2, ii++)
    {
        doubleDigit[ii] = cardDigits[i] * 2;
    }

    // add the digits in the array

    int doubleSum = 0;

    for (int i = 0; i <= ((cardLength - 2) / 2); i++)
    {
        if (doubleDigit[i] > 9)
        {
            doubleSum += floor(doubleDigit[i] / 10) + (doubleDigit[i] % 10);
        }
        else
        {
            doubleSum += doubleDigit[i];
        }
    }

    // sum remaining (non-doubled) digits
    int normalSum = 0;

    for (int k = cardLength - 1; k >= 0; k -= 2)
    {
        int normalDigit = cardDigits[k];
        normalSum += normalDigit;
    }

    // add these and check if last digit is 0

    if ((doubleSum + normalSum) % 10 == 0)
    {
        // if valid, check for type of card (MC, VISA, AMEX)
        switch (cardDigits[0])
        {
            case 3:
                if ((cardDigits[1] == 4 || cardDigits[1] == 7) && cardLength == 15)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;

            case 4:
                if (cardLength == 13 || cardLength == 16)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;

            case 5:
                if ((cardDigits[1] == 1 || cardDigits[1] == 2 || cardDigits[1] == 3 || cardDigits[1] == 4 || cardDigits[1] == 5) &&
                    cardLength == 16)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;

            default:
                printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}