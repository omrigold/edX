from cs50 import get_string
import re


def main():
    # request a string from the user
    text = get_string("Text:  ")

    # find all letters, words, and sentences in the text
    letters = re.findall("[a-zA-Z]", text)
    words = text.split()
    sentences = re.findall("[.?!]", text)

    # print stats
    l_cnt = len(letters)
    w_cnt = len(words)
    s_cnt = len(sentences)
    print(f"{l_cnt} letter(s)\n{w_cnt} word(s)\n{s_cnt} sentence(s)")

    # compute Coleman-Liau index of text
    index = 0.0588 * (100.0 * l_cnt / w_cnt) - 0.296 * (100.0 * s_cnt / w_cnt) - 15.8

    # print grade level
    if index < 1.0:
        print("Before Grade 1")
    elif index >= 16.0:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


# call main
main()