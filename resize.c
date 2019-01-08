/* Resizes a BMP file
   use by ex) ./resize .25 large.bmp small.bmp
              ./resize 4 small.bmp large.bmp
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    float f;
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize float-value infile outfile\n");
        return 1;
    }
    else if (sscanf(argv[1], "%f", &f) != 1)
    {
        fprintf(stderr, "Usage: resize float-value infile outfile\n");
        return 1;
    }
    else if (atof(argv[1]) < 0.0 || atoi(argv[1]) > 100.0)
    {
        fprintf(stderr, "Usage: float-value should be (0.0, 100]\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // remember width and height values for original image
    int before_width = bi.biWidth;
    int before_height = abs(bi.biWidth);

    // change header info for width and height with resized information
    bi.biWidth = floor(before_width * f);
    bi.biHeight = 0x00 - floor(before_height * f);

    // determine padding for scanlines
    int original_padding = (4 - (before_width * sizeof(RGBTRIPLE)) % 4) % 4;
    int resized_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // change header info for size of image and file with resized information
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + resized_padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // divide resizing value into integer and floating-point values
    int int_value = floor(f);
    float f_value = f - int_value;

    // calculate additional number of pixels for resizing floating-point values
    int add_w = bi.biWidth % before_width;

    // calculate interval values to skip through pixels
    int skip_w = 1;
    if (add_w != 0)
    {
        skip_w = floor(before_width / add_w);
    }

    // calculate additional number of lines for resizing floating-point values
    int add_h = bi.biHeight % before_height;

    // calculate interval values to skip through lines
    int skip_h = 1;
    if (add_h != 0)
    {
        skip_h = floor(before_height / add_h);
    }

    // create a temporary storage for the resized line
    RGBTRIPLE *line = malloc(sizeof(RGBTRIPLE) * abs(bi.biHeight));

    // iterate over infile's scanlines: use resized height value for iterating
    for (int i = 0; i < before_height; i++)
    {
        // iterate over pixels in scanline: use before_width value for iterating
        for (int j = 0, count_w = 0, add_pixel = 0; j < before_width; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // if the resizing value is greater or equal to 1, must iterate over each pixels of original infile
            if (int_value >= 1)
            {
                // write RGB triple to line storage int_value times
                for (int k = 0; k < int_value; k ++)
                {
                    // store in temporary storage
                    line[count_w++] = triple;
                }
            }
            // if there is a floating-point value to resize, must include additional pixels to fill in margin
            if (f_value > 0)
            {
                // add pixel every skip value as long as count not satisfied
                if (((j % skip_w) == 0) && (add_pixel != add_w))
                {
                    // write RGB triple to line storage
                    line[count_w++] = triple;

                    // decrease count value to keep track of number of pixels more needed
                    add_pixel++;
                }
            }
        }
        // if resizing value is greater than 1, must iterate over line again
        if (int_value >= 1)
        {
            // write the stored line int_values times to output file
            for (int k = 0; k < int_value; k++)
            {
                fwrite(line, sizeof(RGBTRIPLE)*abs(bi.biHeight), 1, outptr);

                // add padding to resized outfile to finish line
                for (int m = 0; m < resized_padding; m++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
        // if there are additional floating point values to resize, include extra lines
        if (f_value > 0)
        {
            // include extra line only every once in a while
            if (((i % skip_h) == 0) && (add_h != 0))
            {
                // write the stored line int_values times to output file
                fwrite(line, sizeof(RGBTRIPLE)*abs(bi.biHeight), 1, outptr);

                // add padding to resized outfile to finish line
                for (int k = 0; k < resized_padding; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
        // skip over padding, if any
        fseek(inptr, original_padding, SEEK_CUR);
    }

    // free memory
    free(line);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
