#include <stdio.h>
#include <malloc.h>

int main()
{
    int m, n, i, j, direction, data;
    scanf("%d", &m);
    scanf("%d", &n);
    scanf("%d", &i);
    scanf("%d", &j);
    scanf("%d", &direction);

    int **p = (int **)malloc(sizeof(int *) * m);
    for (int i = 0; i < m; i++)
        p[i] = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &data);
            p[i][j] = data;
        }
    
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            if (p[i][j] == 1)
                p[i][j] = 2;
        }
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d", p[i][j]);
        if (i != m-1)
            printf("\n");
    }
}