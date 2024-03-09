#include <stdio.h>

#define ERROR 0
#define OK 1
#define SIZE 100

typedef int Status;

Status Count(int *number);
Status InitNumber(int *number);

int main()
{
    int number[4];
    InitNumber(&number[0]);
    Count(&number[0]);
    for (int i = 0; i < number[1]; i++)
        printf("1 ");
    for (int i = 0; i < number[2]; i++)
        printf("2 ");    
    for (int i = 0; i < number[3]; i++)
        printf("3 ");
}

Status Count(int *number)
{
    char c = ' ';
    int data;
    while (c != '\n')
    {
        scanf("%d", &data);
        if (data == 1)
            number[1]++;
        else if (data == 2)
            number[2]++;
        else
            number[3]++;
        c = getchar();
    }
}

Status InitNumber(int *number)
{
    for (int i = 1; i <= 3; i++)
        number[i] = 0;
}