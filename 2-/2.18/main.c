#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define ERROR 0
#define OK 1

typedef int ElemType;
typedef int Status;
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

void InitList_L(LinkList *L);
void CreateList_L(LinkList *L, int n);
Status DeleteList_L(LinkList *L, int i);

int main()
{
    LinkList L, p;
    ElemType data[500];
    char c;
    int del, n;

    InitList_L(&L);
    scanf("%d", &data[0]);

    for(n = 1; (c = getchar()) != '\n'; n++)
        scanf("%d", &data[n]);
    CreateList_L(&L, n);
    p = L;

    for (int i = 0; i < n; i++)
    {
        p = p->next;
        p->data = data[i];
    }

    scanf("%d", &del);
    DeleteList_L(&L, del);

    p = L;
    if (n != 1)
    {    
        for (int i = 0; i < n-1; i++)
        {
            p = p->next;
            if (i != n-1)
                printf("%d ", p->data);
            else
                printf("%d", p->data);
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

void CreateList_L(LinkList *L, int n)
{
    LinkList p;
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;
    for (int i = 0; i < n; i++)
    {
        p = (LinkList)malloc(sizeof(LNode));
        p->data = rand();
        p->next = (*L)->next;
        (*L)->next = p;
    }
}

Status DeleteList_L(LinkList *L, int i)
{
    LinkList p, q;
    p = *L;
    int j = 0;
    while (p->next && j < i)
    {
        p = p->next;
        j++;
    }
    if (!(p->next) || j > i)
        return ERROR;
    q = p->next;
    p->next = q->next;
    free(q);
    return OK;
}