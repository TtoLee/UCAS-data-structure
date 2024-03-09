#include <stdio.h>
#include<malloc.h> 

#define MAXINT 4294967295
#define ERROR -1

unsigned long int *arr;

int factorial(int n, int arrsize);

int main()
{
    int n, arrsize, i;
    scanf("%d %d", &n, &arrsize);
    arr = (unsigned long int *)malloc(sizeof(unsigned long int) * arrsize);
    arr[0] = 1;
    int state = factorial(n, arrsize);
    if(!state)
        printf("%d", ERROR);
    else
    {
        for (i = 0; i < n-1; i++)
            printf("%d ", arr[i]);
        printf("%d", arr[i]);
    }
}

int factorial(int n, int arrsize)
{
    static unsigned long int max = MAXINT;
    if (n > arrsize)
        return 0;
    for (int i = 1; i < n; i++)
    {
        max = max/i/2;
        if (max)
            arr[i] = arr[i-1] * i * 2;
        else 
            return 0;
    }
    return 1;
}