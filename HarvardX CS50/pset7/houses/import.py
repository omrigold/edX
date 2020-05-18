import cs50
import csv
import sys


def main():
    # check number of arguments
    if len(sys.argv) != 2:
        print("Usage: python import.py data(.csv)")
        exit(1)

    # open database
    db = cs50.SQL("sqlite:///students.db")

    # open csv for import
    with open(sys.argv[1], "r") as csvfile:
        students = csv.DictReader(csvfile)

        for student in students:
            name, house, birth = student["name"].split(), student["house"], student["birth"]
            if len(name) == 2:
                first, middle, last = name[0], None, name[1]
            else:
                first, middle, last = name[0], name[1], name[2]

            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?,?,?,?,?);", first, middle, last, house, birth)


main()