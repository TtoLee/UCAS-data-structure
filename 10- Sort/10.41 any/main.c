#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 10000

int main(){
    int max = -1;
    int data;

    int *number = (int *)malloc(MAXNUM * sizeof(int));
    for (int i = 0; i < MAXNUM; i++)
        number[i] = 0;

    while (scanf("%d", &data) != EOF)
    {
        number[data]++;
        if (data > max)
            max = data;
    }
    int flag = 0;
    for (int i = 0; i <= max; i++){
        while (number[i])
        {
            if (flag)
                printf(" ");
            flag = 1;
            printf("%d", i);
            number[i]--;
        }
    }
}