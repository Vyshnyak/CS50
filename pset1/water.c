#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("minutes: ");
    int minutes = GetInt();
    int bottles;
    bottles = minutes * 12;
    
    if (bottles >= 0)
    {
        printf("bottles: %i\n", bottles);
    }
}