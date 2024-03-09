#include <stdio.h>
#include <malloc.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OVERFLOW 0
#define ERROR 0
#define OK 1

typedef char ElemType;
typedef int Status;

typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
}SqList;

Status InitList_Sq (SqList *L);
Status ListInsert_Sq (SqList *L, int i, ElemType e);

int main()
{
    SqList A, B;
    char c;
    int check;

    InitList_Sq (&A);
    InitList_Sq (&B);

    for (int i = 0; (c = getchar()) != '\n'; i++)
    {
        if (i == 0)
            ListInsert_Sq (&A, 1, c);
        else
        {
            scanf ("%c", &c);
            ListInsert_Sq (&A, i+1, c);
        }
    }
    for (int i = 0; (c = getchar()) != '\n'; i++)
    {
        if (i == 0)
            ListInsert_Sq (&B, 1, c);
        else
        {
            scanf ("%c", &c);
            ListInsert_Sq (&B, i+1, c);
        }
    }

    for (check = 0; check <= A.length || check <= B.length; check++)
    {
        if (A.elem[check] != B.elem[check])
        {
            check--;
            break;
        }
        if (check == A.length || check == B.length)
            break;
    }

    if (check == A.length)
    {
        if (check == B.length)
            printf("0");
        else if (check < B.length)
            printf("1");
    }
    else if (check == B.length)
        printf("2");
    else
    {
        if (A.elem[check+1] > B.elem[check+1])
            printf("2");
        else if (A.elem[check+1] < B.elem[check+1])
            printf("1");
        else if (A.elem[check+1] == B.elem[check+1])
            printf("0");
    }
}

Status InitList_Sq (SqList *L)
{
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L->elem)
        return(OVERFLOW);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert_Sq (SqList *L, int i, ElemType e)
{
    ElemType *p;
    if (i < 1 || i > L->length+1)
        return ERROR;
    if (L->length >= L->listsize)
    {
        ElemType *newbase = (ElemType *) realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            return ERROR;
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    ElemType *q = &(L->elem[i-1]);
    for ( p = &(L->elem[L->length-1]); p >= q; --p)
        *(p+1) = *p;
    *q = e;
    ++L->length;
    return OK;
}
