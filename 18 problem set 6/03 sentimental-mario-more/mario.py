# TODO
from cs50 import get_int


def main():
    num = get_int("Height: ")
    while num < 1 or num > 8:
        num = get_int("Height: ")
    for hash in range(1, num + 1):
        for i in range(num - hash):
            print(" ", end="")
        for j in range(hash):
            print("#", end="")
        print("  ", end="")
        for k in range(hash):
            print("#", end="")
        print()


main()
