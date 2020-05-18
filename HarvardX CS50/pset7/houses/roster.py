import cs50
import sys


def main():
    # check number of arguments
    if len(sys.argv) != 2:
        print("Usage: python roster.py house_name")
        exit(1)

    house = sys.argv[1]

    # open database
    db = cs50.SQL("sqlite:///students.db")

    # query for given house in alphabetical order
    rows = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last ASC, first ASC", house)

    if len(rows) == 0:
        print(f"Sorry, no students match house {house}.")
        exit(1)

    # print student roster
    for row in rows:
        first, middle, last, birth = row["first"], row["middle"], row["last"], row["birth"]
        print(f"{' '.join(filter(None,(first, middle, last)))}, born {birth}")


main()