/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n <= 0)
    {
        return false;
    }
    
    int low, high, middle;
    low = 0;
    high = n - 1;
    while (low <= high)
    {
        middle = (low + high) / 2;
        if (value < values[middle])
            high = middle - 1;
        else if (value > values[middle])
            low = middle + 1;
        else 
            return true;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int element = values[i];
        int j = i;
        
        while(j > 0 && values[j - 1] > element)
        {
            values[j] = values[j - 1];
            j--;
        }
        values[j] = element;
    }
}