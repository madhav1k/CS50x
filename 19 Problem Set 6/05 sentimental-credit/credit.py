# TODO
from cs50 import get_int
import math


def main():
    cardNumber = get_int("Number: ")
    while cardNumber <= 0:
        cardNumber = get_int("Number: ")
    cardLength = math.floor(math.log10(cardNumber)) + 1
    cardDigits = [0] * cardLength
    for i in range(cardLength - 1, -1, -1):
        cardDigits[i] = cardNumber % 10
        cardNumber = math.floor(cardNumber / 10)
    doubleDigit = []
    for i in range(cardLength - 2, -1, -2):
        doubleDigit.append(cardDigits[i] * 2)
    doubleSum = 0
    for i in range(len(doubleDigit)):
        if doubleDigit[i] > 9:
            doubleSum += math.floor(doubleDigit[i] / 10) + (doubleDigit[i] % 10)
        else:
            doubleSum += doubleDigit[i]
    normalSum = 0
    for i in range(cardLength - 1, -1, -2):
        normalDigit = cardDigits[i]
        normalSum += normalDigit
    if (doubleSum + normalSum) % 10 == 0:
        if cardDigits[0] == 3:
            if (cardDigits[1] == 4 or cardDigits[1] == 7) and cardLength == 15:
                print("AMEX")
            else:
                print("INVALID")
        elif cardDigits[0] == 4:
            if cardLength == 13 or cardLength == 16:
                print("VISA")
            else:
                print("INVALID")
        elif cardDigits[0] == 5:
            if (
                cardDigits[1] == 1
                or cardDigits[1] == 2
                or cardDigits[1] == 3
                or cardDigits[1] == 4
                or cardDigits[1] == 5
            ) and cardLength == 16:
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")
    return 0


main()
