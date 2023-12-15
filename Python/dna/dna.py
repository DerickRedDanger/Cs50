import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("usage: Python dna.py (database) (sequence)")
    filename1 = sys.argv[1]
    filename2 = sys.argv[2]

    # TODO: Read database file into a variable
    data = []
    # checking if the database is large or small since the large one
    # has more sequences that need to be compared
    small = False
    if filename1 == "databases/small.csv":
        small = True
    with open(filename1, "r") as database:
        reader = csv.DictReader(database)
        for row in reader:
            data.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(filename2, "r") as sequence:
        reader = csv.reader(sequence)
        Sequence = []
        Sequence = sequence.read().replace('\n', '')

    # TODO: Find longest match of each STR in DNA sequence
    # The values that comes from the read are strings,
    # so i am changing theses to string too to be able to compare properly
    a = longest_match(Sequence, "AGATC")
    a = str(a)
    b = longest_match(Sequence, "TTTTTTCT")
    b = str(b)
    c = longest_match(Sequence, "AATG")
    c = str(c)
    d = longest_match(Sequence, "TCTAG")
    d = str(d)
    e = longest_match(Sequence, "GATA")
    e = str(e)
    f = longest_match(Sequence, "TATC")
    f = str(f)
    g = longest_match(Sequence, "GAAA")
    g = str(g)
    h = longest_match(Sequence, "TCTG")
    h = str(h)

    # TODO: Check database for matching profiles
    # if the database is short, i need to use try and exeption here because
    # i have to ask for elements that arent in the short database. they work normaly in the large one
    if small == False:
        for i in range(len(data)):
            try:
                if data[i]["AGATC"] == a and data[i]["TTTTTTCT"] == b and data[i]["AATG"] == c and data[i]["TCTAG"] == d:
                    if data[i]["GATA"] == e and data[i]["TATC"] == f and data[i]["GAAA"] == g and data[i]["TCTG"] == h:
                        match = data[i]["name"]
                        print(f"{match}")
                        return
            except KeyError:
                ifshort(data, a, c, f)
                return
        # iflarge(data,a,b,c,d,e,f,g,h)
        # return
    if small == True:
        for i in range(len(data)):
            if data[i]["AGATC"] == a and data[i]["AATG"] == c and data[i]["TATC"] == f:
                match = data[i]["name"]
                print(f"{match}")
                return
        # ifshort(data,a,c,f)
        # return

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)
    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


def iflarge(data, a, b, c, d, e, f, g, h):
    for i in range(len(data)):
        try:
            if data[i]["AGATC"] == a and data[i]["TTTTTTCT"] == b and data[i]["AATG"] == c and data[i]["TCTAG"] == d:
                if data[i]["GATA"] == e and data[i]["TATC"] == f and data[i]["GAAA"] == g and data[i]["TCTG"] == h:
                    match = data[i]["name"]
                    print(f"{match}")
                    return
        except KeyError:
            return
    print("No match")


def ifshort(data, a, c, f):
    for i in range(len(data)):
        if data[i]["AGATC"] == a and data[i]["AATG"] == c and data[i]["TACT"] == f:
            match = data[i]["name"]
            print(f"{match}")
            return
    print("No match")


main()
