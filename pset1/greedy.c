#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    do
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
    while (change < 0);
    
    int MinNumCoins = 0;
    int IntChange = round(change * 100);
    
    while (IntChange >= 25)
    {
        IntChange = IntChange - 25;
        MinNumCoins++;
    }
    while (IntChange >= 10)
    {
        IntChange = IntChange - 10;
        MinNumCoins++;
    }
    while (IntChange >= 5)
    {
        IntChange = IntChange - 5;
        MinNumCoins++;
    }
    while (IntChange > 0)
    {
        IntChange = IntChange - 1;
        MinNumCoins++;
    }
    printf("%i\n", MinNumCoins);
}