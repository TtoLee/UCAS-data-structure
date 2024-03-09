#include <stdio.h>
#include <malloc.h>

#define MAX_TREE_SIZE 100
#define FALSE 0
#define TRUE 1 

typedef int Status;
typedef int TElemType;

Status SearchChild(TElemType Lchildren[], TElemType Rchildren[], TElemType u, TElemType v);

int main()
{
    char c;
    TElemType data;
    int n, u, v, state;
    n = 0;

    TElemType Lchildren[MAX_TREE_SIZE], Rchildren[MAX_TREE_SIZE];
    scanf("%d", &data);
    Lchildren[0] = data;
    while ((c = getchar()) != '\n')
    {
        scanf("%d", &data);
        Lchildren[++n] = data;
    }
    for (int i = 0; i <= n; i++)
    {
        scanf("%d", &data);
        Rchildren[i] = data;
    }
    scanf("%d %d", &u, &v);

    state = SearchChild(Lchildren, Rchildren, u, v);
    printf("%d", state);
}

Status SearchChild(TElemType Lchildren[], TElemType Rchildren[], TElemType u, TElemType v)
{
    if (Lchildren[v] == u || Rchildren[v] == u)
        return TRUE;
    else
    {
        if (Lchildren[v] != 0 && SearchChild(Lchildren, Rchildren, u, Lchildren[v]))
            return TRUE;
        if (Rchildren[v] != 0 && SearchChild(Lchildren, Rchildren, u, Rchildren[v]))
            return TRUE;
    }
    return FALSE;
}