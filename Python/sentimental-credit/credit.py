# TODO
from cs50 import get_string
from cs50 import get_int

while True:
    try:
        card = get_int("the card number is ")
    except ValueError:
        print("it must be all numbers")
#    if len(card) > 16 or len(card) < 13:
#        print("it must contain between 13 and 16 digits ")
    else:
        break
tipe = 0  # to see which kind of card it could be
x = 0  # to see how many numbers are in the card and which numbers are even or odd
mult = 0  # initialising to later sum the multiplications
mult = int(mult)  # setting to int to truncate the values
sum = 0  # initialising to later sum the sum
sum = int(sum)  # setting to int to truncate the values
while card >= 1:  # till we get to the last digit
    x += 1
    if x % 2 == 0:  # if even, mult by two than sum to the mult
        mult = mult + int(((2 * (card % 10)) / 10) % 10) + int(2 * (card % 10) % 10)
    else:  # if odd, just sum to the sum
        sum = sum + int(card % 10)
    card = card // 10  # removes the last digit of the car
# if the first two digits are 34 or 37, it's a AMEX card
    if card == 34 or card == 37:
        tipe = 1
# if the first two digitas are between 51 and 55, it's a MASTERCARD
    if card >= 51 and card <= 55:
        tipe = 2
# if the first digit is 4, it's a Visa card
    if card == 4:
        tipe = 3
total = sum + mult
lastdig = total % 10
# seeing if the card is valid and AMEX
if lastdig == 0 and x == 15 and tipe == 1:
    print("AMEX")
# seeing if the card is valid and MASTERCARD
elif lastdig == 0 and x == 16 and tipe == 2:
    print("MASTERCARD")
# seeing if the card is valid and VISA
elif lastdig == 0 and x == 13 and tipe == 3:
    print("VISA")
# seeing if the card is valid and VISA
elif lastdig == 0 and x == 16 and tipe == 3:
    print("VISA")
# if it's not one of the above, it's INVALID
else:
    print("INVALID")