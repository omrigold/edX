#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // request string of text
    string text = get_string("Text: ");

    // initialize variables
    int letters = 0;
    int words = 1;
    int sentences = 0;

    // count word stats
    for (int i = 0; i < strlen(text); i++)
    {
        if (toupper(text[i]) >= 65 && toupper(text[i]) <= 90)
        {
            letters++;
        }
        else if (text[i] == 32)
        {
            words++;
        }
        else if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }
    printf("%d letter(s)\n%d word(s)\n%d sentence(s)\n", letters, words, sentences);

    // compute Coleman-Liau index of text
    float index = 0.0588 * ((float) letters / (float) words * 100) - 0.296 * ((float) sentences / (float) words * 100) - 15.8;

    // output grade assessment
    if (index < 1.0)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16.0)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", (int) round(index));
    }
}
