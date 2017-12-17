#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do 
    {
        printf("height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);
    
    int loops = 0;
    int s = height - 1;
    int s2 = 2;
    int h = 1;
    int h2 = 1;

    while (loops < height)
    {
        for (int space = 0; space < s; space++)
        {
            printf(" ");
        }
        for (int hash = 0; hash < h; hash++)
        {
            printf("#");
        }
        for (int space2 = 0; space2 < s2; space2++)
        {
            printf(" ");
        }
        for (int hash2 = 0; hash2 < h2; hash2++)
        {
            printf("#");
        }
        printf("\n");
        loops++;
        s--;
        h++;
        h2++;
    }
}