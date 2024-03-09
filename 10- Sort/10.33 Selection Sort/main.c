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
Status CreateList(SLinkListType *L);
Status SelectSort (SLinkListType *L);
int SelectMinKey(SLinkListType *L, int i);

int main()
{
    SLinkListType L;

    InitList(&L);
    CreateList(&L);
    SelectSort(&L);
    
    for (int i = 1; i <= L.length; i++)
        printf("%d ", L.r[i].rc);
}

Status InitList(SLinkListType *L)
{
    L->r = (SLNode *)malloc(SIZE * sizeof(SLNode));
    L->length = 0;
    return OK;
}

Status CreateList(SLinkListType *L)
{
    RcdType data;
    char c = ' ';

    while (c != '\n')
    {
        scanf("%d", &data);
        L->length++;
        L->r[L->length].rc = data;
        L->r[L->length].next = 0;
        c = getchar();
    }
    return OK;
}

Status SelectSort (SLinkListType *L)
{
    for (int i = 1; i <= L->length; i++)
    {
        int j = SelectMinKey(L, i);
        if (i != j)
        {
            SLNode temp = L->r[i];
            L->r[i] = L->r[j];
            L->r[j] = temp;
        }
    }
}

int SelectMinKey(SLinkListType *L, int i)
{
    int max = INT_MAX;
    int position = i;
    for (int j = i; j <= L->length; j++)
        if (L->r[j].rc < max)
        {
            max = L->r[j].rc;
            position = j;
        }
    return position;
}