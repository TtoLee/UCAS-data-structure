#include <stdio.h>

int g(int m, int n);

int main()
{
    int m, n, result;
    scanf("%d,%d", &m, &n);
    result = g(m, n);
    printf("%d", result);
}

int g(int m, int n)
{
    if (m == 0)
        return 0;
    else
        return g(m-1, 2*n) + n;
}