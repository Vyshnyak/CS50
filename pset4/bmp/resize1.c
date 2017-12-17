/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize num infile outfile\n");
        return 1;
    }

    // remember filenames and the number to which the size will be increased
    int num = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
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
    
    // remember values of the old struct parameters
    int bWidth = bi.biWidth;
    int bHeigth = bi.biHeight;
    
    //// determine padding for infile scanlines 
    int paddingInFile = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // updating width and height parameters of header struct
    bi.biWidth *= num; 
    bi.biHeight *= num;
    
    // determine padding for outfile scanlines
    int paddingOutFile = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // updating size of image and bmp file
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + paddingOutFile) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bHeigth); i < biHeight; i++)
    {
        // temporary storage
            RGBTRIPLE triple;
            
        // resizing horizontally    
        // iterate over pixels in scanline
        for (int c = 0; c < num - 1; c++)
        {
            for (int j = 0; j < bWidth; j++)
            {
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfi
                for (int b = 0; b < num; b++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // padding with zeros to get size of scanlines miltiple by 4
            for (int k = 0; k < paddingOutFile; k++)
            {
                fputc(0x00, outptr);
            }
            
            // return infile's indicator to the start of the scanline
            fseek(inptr, -(bWidth * 3), SEEK_CUR);
        }
        
        // resizing vertically
        // iterate over pixels in last scanline
        for (int j = 0; j < bWidth; j++)
        {
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
            // write RGB triple to outfile
            for (int b = 0; b < num; b++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
            
        // skip over padding, if any, to the next scanline
        fseek(inptr, paddingInFile, SEEK_CUR);
            
        // padding with zeros to get size of scanlines miltiple by 4
        for (int k = 0; k < paddingOutFile; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
