// Accept a cipher and encrypt a message

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    // error if 0, 2+ arguments
    if (argc != 2)
    {
        printf("This program accepts a cipher and no other arguments.\n");
        return 1;
    }
    // error if cipher isn't 26 chars
    else if (strlen(argv[1]) != 26)
    {
        printf("The cipher must contain exactly 26 letters.\n");
        return 1;
    }
    // otherwise perform remaining tests and execute encryption program
    else
    {
        int cipher[26];
        bool check[26] = {0};
        char c;

        // check whether cipher uses all characters only once
        for (int i = 0; i < 26; i++)
        {
            c = argv[1][i];
            if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
            {
                if (check[toupper(c) - 65] == 0)
                {
                    check[toupper(c) - 65] = 1;
                }
                else
                {
                    printf("You have repeating characters in your cipher.\n");
                    return 1;
                }
            }
            else
            {
                printf("You have invalid characters in your cipher.\n");
                return 1;
            }
        }

        // load the cipher
        for (int i = 0; i < 26; i++)
        {
            // store just the difference between the cipher-provided letter and alphabet letter of the same position
            cipher[i] = toupper(argv[1][i]) - (i + 65);
        }

        // get a message to encrypt from the user
        string plain = get_string("plaintext: ");

        // encrypt that message using the cipher
        printf("ciphertext: ");
        for (int i = 0; i < strlen(plain); i++)
        {
            c = plain[i];
            if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
            {
                printf("%c", c + cipher[toupper(c) - 65]);
            }
            else
            {
                printf("%c", c);
            }
        }

        printf("\n");
        return 0;
    }
}

