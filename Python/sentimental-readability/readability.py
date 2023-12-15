# TODO
from cs50 import get_string

text = get_string("Text:  ")  # counting the number of chars in the string text
# initial value of sentences
s = 0
# initial value of letters
l = 0
# initial value of words
w = 1
#  running through the string to check if the chars are letters, and counting words and sentences
for x in text:
    # if it is a letter
    if x.isalpha():
        l += 1
# seeing if there is a . or ! or ? to count sentences
    elif x == "." or x == "!" or x == "?":
        s += 1
# seeing if there is a space or if it's the end of the string to count words
    elif x == " " or x == '\0':
        w += 1
# making the math letters/words * 100 words
L = (l / w) * 100.0
# making the math sentence/words * 100 words
S = (s / w) * 100.0
# finding the grade
grade = 0.0588 * L - 0.296 * S - 15.8
# rounding up the grade
grade = round(grade)
# if the grade is bellow 1, say before grade 1
if grade < 1:
    print("Before Grade 1")
# if the grade is above 16 say grade 16+
elif grade > 16:
    print("Grade 16+")
# if grade is between 1 and 16 say the grade.
else:
    print(f"Grade {grade}")
