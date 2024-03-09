#include <stdio.h>  
#include <malloc.h> 
#include <limits.h>
#define INITSIZE 100
#define INCREMENTSIZE 10
#define OK 1
#define ERROR 0
#define SIZE 100

typedef struct 
{
    int min;
    int max;
} min_max;
typedef int Status;
typedef int RcdType;
typedef min_max ElemType;
typedef struct 
{
    ElemType *top;
    ElemType *base;
    int stacksize;
} Sqstack;

typedef struct
{
    int *r;
    int length;
} SLinkListType;

Status Initstack (Sqstack *s);
Status Push (Sqstack *s, ElemType *e);
Status Pop (Sqstack *s, ElemType *e);
int Empty (Sqstack *s);
Status InitList(SLinkListType *L);
Status CreateList(SLinkListType *L);
Status InsertSort(SLinkListType *L, int min, int max);
int QSort (SLinkListType *L, int low, int high);
Status swap(SLinkListType *L, int i, int j);


int main()
{
    SLinkListType L;
    Sqstack S;

    InitList(&L);
    CreateList(&L);

    Initstack(&S);
    min_max ini = {1, L.length + 1};
    Push(&S, &ini);

    while (!Empty(&S))
    {
        min_max data;
        Pop(&S, &data);
        if (data.max - data.min <= 3)
            InsertSort(&L, data.min, data.max);
        else
        {
            int bound = QSort(&L, data.min, data.max);
            swap(&L, data.min, bound);

            min_max tem1 = {data.min, bound};
            Push(&S, &tem1);
            min_max tem2 = {bound + 1, data.max};
            Push(&S, &tem2);
        }
    }

    for (int i = 1; i <= L.length; i++)
        printf("%d ", L.r[i]);

}

Status InitList(SLinkListType *L)
{
    L->r = (int *)malloc(SIZE * sizeof(int));
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
        L->r[L->length] = data;
        c = getchar();
    }
    return OK;
}

Status InsertSort(SLinkListType *L, int min, int max)
{
    int position, number;
    for (int i = min; i < max; i++)
    {
        number = INT_MAX;
        for (int j = i; j < max; j++)
        {
            if (L->r[j] < number)
            {
                number = L->r[j];
                position = j;
            }
        }
        swap(L, position, i);
    }
    return OK;
}

int QSort (SLinkListType *L, int low, int high)
{
    int last = low + 1;
    for (int i = low + 1; i < high; i++)
    {
        if (L->r[i] < L->r[low])
        {
            swap(L, i, last);
            last++;
        }
    }
    return last - 1;
}

Status swap(SLinkListType *L, int i, int j)
{
    int tem = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = tem;
}


Status Initstack (Sqstack *s)
{
    s->base = (ElemType *)malloc(INITSIZE * sizeof(ElemType));
    if (!s)
        return ERROR;
    s->top = s->base;
    s->stacksize = INITSIZE;
    return OK;   
}

Status Push (Sqstack *s, ElemType *e)
{
    if (s->top >= s->base + s->stacksize)
    {
        s->base = (ElemType *)realloc(s->base, (s->stacksize + INCREMENTSIZE) * sizeof(ElemType));
        if (!s->base)
            return ERROR;
        s->stacksize += INCREMENTSIZE;
    }
    *(s->top) = *e;
    s->top++;
    return OK;
}

Status Pop (Sqstack *s, ElemType *e)
{
    if (s->top != s->base)
    {
        s->top--;
        *e = *(s->top);
    }
    else 
        return ERROR;
    return OK;
}

int Empty (Sqstack *s)
{
    if (s->base == s->top)
        return 1;
    return 0;
}