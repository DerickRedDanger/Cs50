# TODO
from cs50 import get_int
while True:  # to keep asking till the right answer is given
    try:
        n = get_int("what's the height ? ")
    except ValueError:
        print("it must be between 1 and 8")
    if n > 8 or n < 1:
        print("it must be between 1 and 8")
    else:  # to break away and continue if given a numer between 1 and 8
        break
for i in range(n):
    for j in range(n - i - 1):
        print(" ", end="")
    for k in range(i + 1):
        print("#", end="")
    print("  ", end="")
    for l in range(i + 1):
        print("#", end="")
    print("")