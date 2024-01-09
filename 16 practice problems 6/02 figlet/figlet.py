from pyfiglet import Figlet
import random
import sys

figlet = Figlet()

if len(sys.argv) == 1:
    font = random.choice(figlet.getFonts())
elif len(sys.argv) == 3 and sys.argv[1] in ["-f", "--font"] and sys.argv[2] in figlet.getFonts():
    font = sys.argv[2]
else:
    sys.exit("Invalid usage")

s = input("Input: ",)
figlet.setFont(font=font)
print("Output:")
print(figlet.renderText(s))
