//inspired from try0recover.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //exactly one command line argument
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    //remeber filenames
    char *infile = argv[1];

    //open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s\n", infile);
        return 2;
    }

    BYTE buffer[512];
    int imagecount = 0;

    char filename[8];
    FILE *outptr = NULL;

    while (true)
    {
        //read the block of memory
        size_t bytesRead = fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr);  //size_t = unassigned integer

        //break out the loop when we reach the end of the file
        if (bytesRead == 0 && feof(inptr))  //feof = check and reset file(infile)
        {
            break;
        }

        //check if we found jpeg format
        bool JPEGheader = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0;

        //if we found a new jpeg.. close the previous one
        if (JPEGheader && outptr != NULL)
        {
            fclose(outptr);
            imagecount++;
        }

        //if we found a jpeg, we need to write that to an output file
        if (JPEGheader)
        {
            sprintf(filename, "%03i.jpg", imagecount);
            outptr = fopen(filename, "w");
        }

        //write anytime we have an open file
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), bytesRead, outptr);
        }
    }

    //close last jpeg fle
    fclose(outptr);

    //close inflie
    fclose(inptr);

    //success
    return 0;
}
