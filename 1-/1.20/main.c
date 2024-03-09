#include <stdio.h>

int main()
{
    int x_ini, x, n, a, result;
    char c;
    scanf ("%d %d", &x_ini, &n);
    x = 1;
    result = 0;
    getchar();
    for (int i = 0; i <= n; i++)
        {
            scanf("%d", &a);
            result += a*x;
            x *= x_ini;
        }
    printf("%d", result);
}