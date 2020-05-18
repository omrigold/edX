from cs50 import get_int


# draw the pyramid
def main():
    h = getPositiveInteger()
    for i in range(h):
        row = i + 1
        print(" " * (h - row) + "#" * row + "  " + "#" * row)


# keep prompting until you get an integer in the proper range
def getPositiveInteger():
    while True:
        height = get_int("Pyramid height (1-8):  ")
        if height > 0 and height <= 8:
            break
    return height


# call the main function
main()
