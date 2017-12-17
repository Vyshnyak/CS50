#include <cs50.h>
#include <stdio.h>

int GetPositiveInt(void);

int main(void)
{
    int minutes = GetPositiveInt();
    
    
    int bottles = minutes * 12;
    printf("bottles: %i\n", bottles);
}

int GetPositiveInt(void)
{
    int min;
    do
    {
        printf("minutes: ");
        min = GetInt();
    }
    while (min <= 0);
    
    return min;
}