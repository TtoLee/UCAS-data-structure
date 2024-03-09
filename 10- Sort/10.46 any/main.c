#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 30000
#define OK 1
#define ERROR 0

typedef struct
{
    int *r;
    int length;
} SLinkListType;
typedef int Status;

Status InitList(SLinkListType *L);
Status CreateList(SLinkListType *L, int n);
Status CountingSort(SLinkListType la, SLinkListType *lc);

int main()
{
    SLinkListType la, lc;
    int n;
    InitList(&la);
    InitList(&lc);

    scanf("%d\n", &n);
    CreateList(&la, n);
    CountingSort (la, &lc);
            
    for (int i = 1; i <= lc.length; i++)
    {
        int max = MAXLEN;
        int position;
        for (int j = 1; j <= lc.length; j++)
        {
            if (lc.r[j] < max)
            {
                max = lc.r[j];
                position = j;
            }
        }
        printf("%d", la.r[position]);
        lc.r[position] = MAXLEN;
        if(i != lc.length)
            printf(" ");
    }
}

Status InitList(SLinkListType *L)
{
    L->r = (int *)malloc(2 * MAXLEN * sizeof(int));
    L->length = 0;
    return OK;
}

Status CreateList(SLinkListType *L, int n)
{
    int data;
    char c = ' ';

    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &data);
        L->r[i] = data;
    }
    L->length = n;
    return OK;
}

Status CountingSort(SLinkListType la, SLinkListType *lc)
{
    for (int i = 1; i <= la.length; i++)
        for (int j = 1; j <= la.length; j++)
            if (la.r[j] < la.r[i])
                lc->r[i]++;
    lc->length = la.length;
    return OK;
}