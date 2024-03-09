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
int LengthList_L(LinkList L);
void ReverseList_L(LinkList *L);

int main()
{
    LinkList L, L_re, p;
    ElemType data[500];
    char c;
    int del, n;

    InitList_L(&L);

    scanf("%c", &data[0]);
    for(n = 1; (c = getchar()) != '\n'; n++)
        scanf("%c", &data[n]);
    CreateList_L(&L, n);
    p = L;

    for (int i = 0; i < n; i++)
    {
        p = p->next;
        p->data = data[i];
    }

    ReverseList_L(&L);

    p = L;
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

void ReverseList_L(LinkList *L)
{
    LinkList p, q, r;
    p = (*L)->next;
    r = NULL; 
    while (p)
    {
        q = p;
        p = p->next;
        q->next = r;
        r = q;
    }
    (*L)->next = q; 
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