// recovers JPEGs from a forensic image

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // Ensure program accepts card file
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover image\n");
        return 1;
    }

    // Open card
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");

    // Ensure card opens, else return error message
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // initialize count to track number of images
    int count = -1;

    // initialize filename
    char *outfile = malloc(sizeof(char) * 7);

    // initialize file pointer for JPEG files
    FILE *outptr;

    // create temporary storage for each 512 bytes
    BYTE *buffer = malloc(sizeof(BYTE) * 512);
    if (buffer == NULL)
    {
        fprintf(stderr, "dynamic memory allocation error\n");
        return 3;
    }

    // initialize buffer_size to keep track of number of bytes read
    int buffer_size;


    // read file by block until end of card
    while (1)
    {
        // read file
        buffer_size = fread(buffer, 1, 512, inptr);

        // exit loop at end of file (EOF)
        if (buffer_size == 0)
        {
            break;
        }

        // check if block is start of JPEG file
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            // increment count
            count++;

            // if a JPEG file is already open
            if (count > 0)
            {
                // close the current JPEG file
                fclose(outptr);
            }
            // open a output file labled with count
            sprintf(outfile, "%03i.jpg", count);
            outptr = fopen(outfile, "w");
            if (outptr == NULL)
            {
                fprintf(stderr, "Could not open %s.\n", outfile);
                return 4;
            }

            // write the buffer to output file
            fwrite(buffer, buffer_size, 1, outptr);
        }
        // if not start of JPEG file
        else
        {
            // if a JPEG file is already open
            if (count >= 0)
            {
                // add buffer to output file
                fwrite(buffer, buffer_size, 1, outptr);
            }
        }
    }
    // add last buffer to last JPEG file
    fwrite(buffer, buffer_size, 1, outptr);

    // close last JPEG file
    fclose(outptr);

    // free temporary storage
    free(buffer);

    // free memory for output file name
    free(outfile);

    return 0;
}
