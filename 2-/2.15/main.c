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
void MergeList_L(LinkList *La, LinkList *Lb, LinkList *Lc);

int main()
{
    LinkList ha, hb, hc, pa, pb, pc;
    int len_a, len_b;
    int data;

    InitList_L(&ha);
    InitList_L(&hb);
    InitList_L(&hc);

    scanf("%d %d", &len_a, &len_b);
    getchar();

    CreateList_L(&ha, len_a);
    CreateList_L(&hb, len_b);
    CreateList_L(&hc, len_a+len_b);

    pa = ha;
    pb = hb;

    for (int i = 0; i < len_a; i++)
    {
        scanf("%d", &data);
        pa = pa->next;
        pa->data = data;
        getchar();
    }
    for (int i = 0; i < len_b; i++)
    {
        scanf("%d", &data);
        pb = pb->next;
        pb->data = data;
        if (i != len_b)
            getchar();
    }

    MergeList_L(&hb, &ha, &hc);
    pc = hc;
    for (int i = 0; i < len_a + len_b; i++)
    {
        pc = pc->next;
        if (i != len_a+len_b)
            printf("%d ", pc->data);
        else
            printf("%d", pc->data);
    }
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

void MergeList_L(LinkList *La, LinkList *Lb, LinkList *Lc)
{
    LinkList pa, pb, pc;
    *Lc = *La;
    pa = (*La)->next;
    pb = (*Lb)->next;
    pc = *Lc;
    while (pa || pb)
    {
        if (pa)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
}