import csv

counter = 0 # say that we wanted to keep count of one show in particular

titles = {} # a dictionarie dict()

with open ("favorites.csv","r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        title = row ["title"].strip().upper() # strip removes spaces from the left and right
        if title in titles:
            titles[titles] += 1
        else:
            titles[title] = 1
        if "OFFICE" in titles:
            counter += 1

def get_valu(title)
    return titles(title)

for title in sorted(titles, key=get_value, reverse=true): # creates of sorted copy of titles,
    #it can also take in a key or function to decide how to sort it
    print(title, titles[titles])

# instead i could also use lambda to create a anonimous function
# a function without a name that would only be used once, intead of defining a new function
for title in sorted(titles, key=lambda title: titles(title)) # so a one use and one line function that takes
# title as input and titles[title] as output
    print(title, titles[titles])

print(f"number of people who like the officer: {counter}")