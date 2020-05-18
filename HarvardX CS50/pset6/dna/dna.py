from cs50 import get_string
import csv
import re
import sys


def main():
    # check for correct number of arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py database(.csv) dna_sequence")
        exit(1)

    # import dna sequence
    dnafile = open(sys.argv[2], 'r')
    dna = dnafile.readline()
    dnafile.close()

    # import csv data
    with open(sys.argv[1]) as csvfile:
        db = csv.DictReader(csvfile)
        sequences = db.fieldnames[1:]

        results = {}
        for seq in sequences:
            results.update({seq: len(max(re.findall(r'(?:'+seq+')+', dna)))/len(seq)})

        # check for dna match
        for row in db:
            match = True
            for seq in sequences:
                # print(row["name"], seq, row[seq], results[seq])
                if int(row[seq]) != int(results[seq]):
                    match = False
                    break
            if match:
                print(row["name"])
                break

        if not match:
            print("No match")


main()