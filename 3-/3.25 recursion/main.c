#include <stdio.h>

int main()
{
    int n, result;
    result = 1;
    scanf("%d", &n);

    for (; n != 0; n /= 2)
        result *= n;

    printf("%d", result);
}