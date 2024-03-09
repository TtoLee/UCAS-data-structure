#include <stdio.h>

int main()
{
    char c;
    int list[100];
    int i, j, num, tem;
    scanf("%d", &list[0]);
    for (i = 1; (c = getchar()) != '\n'; i++)
        scanf("%d", &list[i]);
    scanf("%d", &num);
    for (j = 0; num >= list[j]; j++);
    for (; j <= i; j++)
    {
        tem = num;
        num = list[j];
        list[j] = tem;
    }
    for (j = 0; j < i; j++)
        printf("%d ", list[j]);
    printf("%d", list[j]);
}