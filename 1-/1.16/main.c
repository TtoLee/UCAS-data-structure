#include <stdio.h>

int main()
{
    int x, y, z, tem;
    scanf("%d %d %d", &x, &y, &z);

    if (x < y)
    {
        tem = x;
        x = y;
        y = tem;
    }

    if (x < z)
    {
        tem = x;
        x = z;
        z = tem;
    }

    if (y < z)
    {
        tem = y;
        y = z;
        z = tem;
    }

    printf("%d %d %d", x, y, z);
}