#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ERROR 0
#define OK 1
#define SIZE 100

typedef int Status;
typedef int RcdType;
typedef struct
{
    RcdType rc;
    int next;
} SLNode;
typedef struct
{
    SLNode *r;
    int length;
} SLinkListType;

Status InitList(SLinkListType *L);
Status CreateList(SLinkListType *L, int n);
Status LInsertion (SLinkListType *L, int n);
Status Arrange (SLinkListType *SL);

int main()
{
    SLinkListType L;
    int n;
    InitList(&L);
    scanf("%d", &n);
    getchar();
    CreateList(&L, n);
    LInsertion(&L, n);
    Arrange(&L);
    for (int i = 1; i <= n; i++)
        printf("%d ", L.r[i].rc);
}

Status InitList(SLinkListType *L)
{
    L->r = (SLNode *)malloc(SIZE * sizeof(SLNode));
    L->length = 0;
    return OK;
}

Status CreateList(SLinkListType *L, int n)
{
    RcdType data;

    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &data);
        L->r[i].rc = data;
        L->length++;
        L->r[i].next = 0;
    }
    return OK;
}

Status LInsertion (SLinkListType *L, int n)
{
    int i, j, k;
    L->r[0].rc = INT_MAX;
    L->r[0].next = 1;
    L->r[1].next = 0;
    for (i = 2; i <= n; i++)
    {
        for (j = 0, k = L->r[0].next; L->r[k].rc <= L->r[i].rc; j = k, k = L->r[k].next);
        L->r[j].next = i;
        L->r[i].next = k;
    }
}

Status Arrange (SLinkListType *SL)
{
    int p, q;
    p = SL->r[0].next;
    for (int i = 1; i < SL->length; i++)
    {
        while (p < i)
            p = SL->r[p].next;
        q = SL->r[p].next;
        if (p != i)
        {
            SLNode temp = SL->r[p];
            SL->r[p] = SL->r[i];
            SL->r[i] = temp;
            SL->r[i].next = p;
        }
        p = q;
    }
}