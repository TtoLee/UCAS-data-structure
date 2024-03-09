#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define ERROR 0
#define OK 1

typedef char ElemType;
typedef int Status;
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

void InitList_L(LinkList *L);
void CreateList_L(LinkList *L);
Status DeleteDifCom_L(LinkList *A, LinkList *B);
Status DeleteSameCom_L(LinkList *A, LinkList *B);
int LengthList_L(LinkList L);

int main()
{
    LinkList A, B, C, p;
    ElemType data[500];
    char c;
    int mink, maxk, n;

    CreateList_L(&A);
    CreateList_L(&B);
    CreateList_L(&C);
    
    DeleteDifCom_L(&B, &C);
    DeleteSameCom_L(&A, &B);

    p = A;
    n = LengthList_L(A);

    if (n != 0)
    {    
        for (int i = 0; i < n; i++)
        {
            p = p->next;
            if (i != n-1)
                printf("%c,", p->data);
            else
                printf("%c", p->data);
        }
    }
    else
        printf("NULL");
        
}

void InitList_L(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;
}

void CreateList_L(LinkList *L)
{
    LinkList p;
    ElemType data[200];
    char c;
    int n;

    scanf("%c", &data[0]);
    for(n = 1; (c = getchar()) != '\n'; n++)
        scanf("%c", &data[n]);

    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;
    for (int i = 0; i < n; i++)
    {
        p = (LinkList)malloc(sizeof(LNode));
        p->data = data[i];
        p->next = (*L)->next;
        (*L)->next = p;
    }

    p = *L;
    for (int i = 0; i < n; i++)
    {
        p = p->next;
        p->data = data[i];
    }
}

Status DeleteDifCom_L(LinkList *A, LinkList *B)
{
    LinkList p, q, r;
    p = *A;
    q = *B;

    while (p->next && q->next)
    {
        if (p->next->data == q->next->data)
        {
            p = p->next;
            q = q->next;
        }
        else if (p->next->data < q->next->data)
        {
            r = p->next;
            p->next = r->next;
            free(r);
        }
        else if (p->next->data > q->next->data)
            q = q->next;
    }
    return OK;
}

Status DeleteSameCom_L(LinkList *A, LinkList *B)
{
    LinkList p, q, r;
    p = *A;
    q = *B;

    while (p->next && q->next)
    {
        if (p->next->data < q->next->data)
            p = p->next;
        else if (p->next->data > q->next->data)
            q = q->next;
        else if (p->next->data == q->next->data)
        {
            r = p->next;
            p->next = r->next;
            free(r);
        }
    }
    return OK;
}

int LengthList_L(LinkList L)
{
    int i = 0;
    LinkList p = L->next;
    while (p)
    {
        i++;
        p = p->next;
    }
    return i;
}