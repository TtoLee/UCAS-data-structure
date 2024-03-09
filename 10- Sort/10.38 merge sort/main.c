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
Status MSort (SLinkListType *L1, SLinkListType *L2, int s, int t);
Status Merge(SLinkListType *L1, SLinkListType *L2, int i, int m, int n);

int main()
{
    SLinkListType la;
    int n;
    InitList(&la);

    scanf("%d\n", &n);
    CreateList(&la, n);
    MSort(&la, &la, 1, la.length);            
    for (int i = 1; i <= la.length; i++)
    {
        printf("%d", la.r[i]);
        if(i != la.length)
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

    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &data);
        L->r[i] = data;
    }
    L->length = n;
    return OK;
}

Status MSort (SLinkListType *L1, SLinkListType *L2, int s, int t)
{
    if (s == t)
        L2->r[s] = L1->r[s];
    else
    {
        SLinkListType L3;
        InitList(&L3);
        L3.length = L1->length;
        int m = (s + t) / 2;
        MSort (L1, &L3, s, m);
        MSort (L1, &L3, m + 1, t);
        Merge (&L3, L2, s, m, t);
    }
}

Status Merge(SLinkListType *L1, SLinkListType *L2, int i, int m, int n)
{
    int j, k;

    for (j = m + 1, k = i; i <= m && j <= n; k++)
    {
        if (L1->r[i] < L1->r[j])
            L2->r[k] = L1->r[i++];
        else
            L2->r[k] = L1->r[j++];
    }
    while (i <= m)
        L2->r[k++] = L1->r[i++];
    while (j <= n)
        L2->r[k++] = L1->r[j++];
    return OK;
}