/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // Проверяет количество вводимых аргументов.
    // Возвращает 1 если количество аргументов не равно 2 и 3.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // Переводит 2-ой аргумент (число) из типа string в тип int.
    int n = atoi(argv[1]);

    // Проверяется условие, в случае если в главной функции 3 аргумента, 
    // то в качестве аргумента функции srand принимается 3 аргумент. 
    // В ином случае в качестве аргумента функции srand принимается количество секунд реального времени
    // которое генерируется с помощью функции time(NULL)
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // Генерация n псевдослучайных чисел в диапазоне от 0 до 65536
    // функция drand48 возвращает число типа double от 0.0 до 1.0, которое потом преобразовывается в тип int и выводится на экран.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}