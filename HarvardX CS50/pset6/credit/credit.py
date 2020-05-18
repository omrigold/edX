from cs50 import get_int


def main():
    # require user input until positive integer provided
    while True:
        cc = get_int("Number:  ")
        if cc > 0:
            break

    # determine card type
    if int(cc / 10000000000000) in [34, 37]:
        output = "AMEX"
    elif int(cc / 1000000000000000) == 4:
        output = "VISA"
    elif int(cc / 100000000000000) in [51, 52, 53, 54, 55]:
        output = "MASTERCARD"
    else:
        print("INVALID")
        exit(1)

    # instantiate variables
    evens, odds, digit = 0, 0, 0

    # Luhn's Algorithm
    while cc > 0:
        odds += cc % 10
        cc = int(cc / 10)
        digit = (cc % 10) * 2
        cc = int(cc / 10)
        while digit > 0:
            evens += digit % 10
            digit = int(digit / 10)

    if (odds + evens) % 10 == 0:
        print(output)
    else:
        print("INVALID")


# call main function
main()