#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Print the key next time!\n");
        return 1;
    }

    int k = atoi(argv[1]);
    
    if (k < 0)
    {
        return 0;
    }
  
    string text = GetString();
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char text2[n];
        
        if (isalpha(text[i]) && isupper(text[i]))
        {
            text2[i] = ((text[i] - 65) + k) % 26;
            text2[i] = text2[i] + 65;
        }
        else if (isalpha(text[i]) && islower(text[i]))
        {
            text2[i] = ((text[i] - 97) + k) % 26;
            text2[i] = text2[i] + 97;
        }
        else
        {
            text2[i] = text[i];
        }
        printf("%c", text2[i]);
    }
    printf("\n");
    return 0;
}

