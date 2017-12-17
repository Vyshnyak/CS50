/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;


int main(void)
{
    // open input file
    FILE* inptr = fopen("card.raw", "r");

    if (inptr == NULL)
    {
        printf("Couldn't open card.raw.\n");
        return 2;
    }
    
    // create an array for bytes
    BYTE buffer[512];
    
    // initializing counter for jpeg files; object of png files; array for jpeg files name
    int jpegs = 0;
    FILE* img = NULL;
    char* filename = malloc(sizeof("000.jpg"));
    
    if (filename == NULL)
    { 
        printf("Error -- out of memory.\n");
        return 3;
    }
    
    // read from input file to an array until getting to EOF
    while (fread (&buffer, 512, 1, inptr) == 1)
    {
        // initializing varaible that shows if we are at the start of jpeg file (0 - false, 1 - true)
        int startOfFile = 0;
        
        // ask if we have reached the start of jpg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // give startOfFile variable true value and increment the count of jpeg files
            startOfFile = 1;
            jpegs++;
        }
        
        // ask if we have reached start of file and if we already found a jpeg file
        if (startOfFile == 1 && jpegs > 0)
        {
            // ask if we at the start of file of very first jpeg file
            if (jpegs == 1)
            {
                // set the name of new jpg file
                sprintf(filename, "%03i.jpg", jpegs - 1);
            
                // open new jpg file
                img = fopen(filename, "w");
            
                if (img == NULL)
                {
                    fclose(inptr);
                    fprintf(stderr, "Could not create %s.\n", filename);
                    return 4;
                }
                
                // write 512 bytes to an array
                fwrite(&buffer, 512, 1, img);
            }
            else 
            {
                // close the previous jpeg file
                fclose(img);
            
                // set the name of new jpg file
                sprintf(filename, "%03i.jpg", jpegs - 1);
            
                // open new jpg file
                img = fopen(filename, "w");
            
                if (img == NULL)
                {
                    fclose(inptr);
                    fprintf(stderr, "Could not create %s.\n", filename);
                    return 4;
                }
                
                // write 512 bytes to an array
                fwrite(&buffer, 512, 1, img);
            }
        }
        //ask if we're not at the start of file and if we already found jpg file
        else if (startOfFile == 0 && jpegs > 0)
        {
            // write 512 bytes to an array
            fwrite(&buffer, 512, 1, img);
        }
    }
    
    // close all of the files
    free(filename);
    fclose(inptr);
    fclose(img);
    
    return 0;
}
