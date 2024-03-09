#include <stdio.h>
#define MAXSIZE 1000

int fib (int k, int m, int fib_array[]);

int main()
{
    int fib_array[MAXSIZE];
    int k, m;
    scanf("%d %d", &k, &m);
    int result = fib(k, m, fib_array);
    printf("%d", result);
}

int fib (int k, int m, int fib_array[])
{
    if (m < k-1)
        return 0;
    else if (m == k-1)
        return 1;
    else
    {
        int i;

        for (i = 0; i < k-1; i++)
            fib_array[i] = 0;
        fib_array[i++] = 1;
        for ( ; i <= m; i++)
        {
            fib_array[i] = 0;
            for (int j = 1; j <= k; j++)
                fib_array[i] += fib_array[i-j];
        }
        return fib_array[m];
    }
}