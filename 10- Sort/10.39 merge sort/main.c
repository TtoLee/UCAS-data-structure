#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 300000
#define OK 1
#define ERROR 0

typedef struct
{
    int *r;
    int length;
} SLinkListType;
typedef int Status;

Status InitList(SLinkListType *L);
Status CreateList(SLinkListType *L);
Status Merge(SLinkListType la, SLinkListType lb, SLinkListType *lc);

int main()
{
    SLinkListType la, lb, lc;
    InitList(&la);
    InitList(&lb);
    InitList(&lc);

    CreateList(&la);
    CreateList(&lb);

    Merge(la, lb, &lc);
    for (int i = 1; i <= lc.length; i++)
        printf("%d ", lc.r[i]);
}

Status InitList(SLinkListType *L)
{
    L->r = (int *)malloc(2 * MAXLEN * sizeof(int));
    L->length = 0;
    return OK;
}

Status CreateList(SLinkListType *L)
{
    int data;
    char c = ' ';

    while (c != '\n')
    {
        scanf("%d", &data);
        L->length++;
        L->r[L->length] = data;
        c = getchar();
    }
    return OK;
}

Status Merge(SLinkListType la, SLinkListType lb, SLinkListType *lc)
{
    int i, j;
    i = 1;
    j = 1;
    for (int k = 1; k <= la.length + lb.length; k++)
    {
        if (i > la.length)
        {
            lc->r[k] = lb.r[j];
            j++;
            lc->length++;
        }
        else if (j > lb.length)
        {
            lc->r[k] = la.r[i];
            i++;
            lc->length++;
        }
        else
        {
            if (la.r[i] < lb.r[j])
            {
                lc->r[k] = la.r[i];
                i++;
                lc->length++;
            }
            else
            {
                lc->r[k] = lb.r[j];
                j++;
                lc->length++;
            }
        }
    }
    return OK;
}