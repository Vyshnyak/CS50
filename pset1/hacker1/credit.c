#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //запрос на ввод номера кредитной карты
    printf("Number: ");
    long num = GetLongLong();
    
    long num1 = num;
    int length = 0;
    long decimal = 1;
    int sum = 0;
    
    // определяем длину числа long для создания массива
    while (num1 != 0)
    {
        num1 /= 10;
        length++;
    }
    
    //проверка на правильность длины введенного числа
    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
        return 0;
    }
    
    int massNum[length];  
    
    //создаем десятичное число под длину числа для разделения числа
    for (int i = 1; i < length; i++)
    {
        decimal *= 10;
    }
    
    //разделяем число на каждый елемент и записываем его в массив
    for (int j = 0; j < length; j++)
    {
        massNum[j] = (num / decimal) % 10;
        decimal /= 10;
    }
    
    //находим сумму каждого второго елемента массива умноженного на 2
    for (int b = length - 2; b >= 0; b -= 2)
    {
        decimal = 10;
        int tempMassNum = massNum[b] * 2;
        
        if (tempMassNum > 9)
        {
            for (int c = 0; c < 2; c++)
            {
                sum += (tempMassNum / decimal) % 10;
                decimal /= 10;
            }
        }
        else
        {
            sum += tempMassNum;
        }
    }
    
    //суммируем число sum с каждым первым елементом массива
    for (int e = length - 1; e >= 0; e -= 2)
    {
        sum += massNum[e];
    }
    
    decimal = 1;
    
    for (int c = 2; c < length; c++)
    {
        decimal *= 10;
    }
    
    bool sumEquals = sum % 10 == 0;
    int first2Num = num / decimal;
    int firstNum = first2Num / 10;
    
    if (sumEquals && (first2Num == 34 || first2Num == 37) && length == 15)
    {
        printf("AMEX\n");
    }
    else if (sumEquals && (first2Num > 50 && first2Num < 56) && length == 16)
    {
        printf("MASTERCARD\n");
    }
    else if (sumEquals && firstNum == 4 && (length == 13 || length == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
    
    return 0;
}