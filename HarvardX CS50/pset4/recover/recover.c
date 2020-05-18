#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check for invalid usage
    if (argc != 2)
    {
        printf("Usage: recover [recovery file name]\n");
        return 1;
    }

    // open the input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("The file %s could not be read.\n", argv[1]);
        return 1;
    }

    // create a binary block
    unsigned char block[512];
    int jpg_count = 0, len = 0;
    char outfile[7];

    // prime the pump to find the first jpg block
    do
    {
        fread(block, sizeof(char), 512, inptr);
    }
    while (!(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] >= 0xe0 && block[3] < 0xf0));

    // find and write jpg files until EOF
    do
    {
        sprintf(outfile, "%03d.jpg", jpg_count);
        FILE *outptr = fopen(outfile, "w");
        do
        {
            fwrite(block, sizeof(char), 512, outptr);
            len = fread(block, sizeof(char), 512, inptr);
        }
        while (len > 0 && !(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] >= 0xe0 && block[3] < 0xf0));
        fclose(outptr);
        jpg_count++;
    }
    while (len > 0);

    fclose(inptr);
    printf("Recovered %d file(s).\n", jpg_count);
    return 0;
}
