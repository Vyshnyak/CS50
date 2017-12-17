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
    while ((height < 0) || (height > 23));
    
    int loops = 0;
    int s = height - 1;
    int h = 2;

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
        printf("\n");
        loops++;
        s--;
        h++;
    }
}