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
    
    string key = argv[1];
    int n2 = strlen(key);
    
    for (int a = 0; a < n2; a++)
    {
        if (isalpha(key[a]) == false)
        {
            printf("The key must contain only an alphabetic symbols!");
            return 1;
        }
    } 
    
    string text = GetString();
    int j = 0;
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char text2[n];
        
        if (isalpha(text[i]) && isupper(text[i]))
        {
            if (isupper(key[j]))
            {
                text2[i] = ((text[i] - 65) + (key[j] - 65)) % 26;
            }
            else if (islower(key[j]))
            {
                text2[i] = ((text[i] - 65) + (key[j] - 97)) % 26;
            }
            text2[i] = text2[i] + 65;
            j = (j + 1) % n2;
        }
        else if (isalpha(text[i]) && islower(text[i]))
        {
            if (islower(key[j]))
            {
                text2[i] = ((text[i] - 97) + (key[j] - 97)) % 26;
            }
            else if (isupper(key[j]))
            {
                text2[i] = ((text[i] - 97) + (key[j] - 65)) % 26;
            }
            text2[i] = text2[i] + 97;
            j = (j + 1) % n2;
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

