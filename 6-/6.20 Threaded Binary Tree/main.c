#include <stdio.h>
#include <malloc.h>

#define MAX_TREE_SIZE 100
#define ERROR 0
#define OK 1 

typedef int Status;
typedef int TElemType;
typedef enum {Link, Thread} PointerTag;
typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *lchild, *rchild;
    PointerTag LTag, RTag;
}BiThrNode, *BiThrTree;

Status CreateBiThrTree(BiThrTree *T, BiThrTree order[], int n);
Status CreateNode(BiThrTree *T, int i, TElemType data[], int lchildren[], int rchildren[], BiThrTree order[], int *used);
Status PreOrderThreading(BiThrTree *Thrt, BiThrTree T);
Status InOrderThreading(BiThrTree *Thrt, BiThrTree T);
Status PostOrderThreading(BiThrTree *Thrt, BiThrTree T);
Status PrintPreorderLeft (BiThrTree Thrt, BiThrTree order[], int n);
Status PrintPreorderRight (BiThrTree Thrt, BiThrTree order[], int n);
Status PrintInorderLeft (BiThrTree Thrt, BiThrTree order[], int n);
Status PrintInorderRight (BiThrTree Thrt, BiThrTree order[], int n);
Status PrintPostorderLeft (BiThrTree Thrt, BiThrTree order[], int n);
Status PrintPostorderRight (BiThrTree Thrt, BiThrTree order[], int n);

int main()
{
    BiThrTree T, Thrt, order[MAX_TREE_SIZE];
    int n;
    scanf("%d", &n);
    CreateBiThrTree(&T, order, n);
    
    PreOrderThreading(&Thrt, T);
    PrintPreorderLeft (Thrt, order, n);
    PrintPreorderRight (Thrt, order, n);

    InOrderThreading(&Thrt, T);
    PrintInorderLeft (Thrt, order, n);
    PrintInorderRight (Thrt, order, n);

    PostOrderThreading(&Thrt, T);
    PrintPostorderLeft (Thrt, order, n);
    PrintPostorderRight (Thrt, order, n);
}

Status CreateBiThrTree(BiThrTree *T, BiThrTree order[], int n)
{
    int used;
    int Lchildren[MAX_TREE_SIZE], Rchildren[MAX_TREE_SIZE];
    TElemType data[MAX_TREE_SIZE];
    used = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d %d %d", &data[i], &Lchildren[i], &Rchildren[i]);
    CreateNode(T, 1, data, Lchildren, Rchildren, order, &used);
    BiThrTree p = *T;
    while (used < n)
    {
        BiThrTree q = p->rchild;
        CreateNode(&q, used + 1, data, Lchildren, Rchildren, order, &used);
        p->rchild = q;
        p = p->rchild;
    }
    return OK;
}

Status CreateNode(BiThrTree *T, int i, TElemType data[], int lchildren[], int rchildren[], BiThrTree order[], int *used)
{
    *T = (BiThrTree)malloc(sizeof(BiThrNode));
    if (!(*T))
        return ERROR;
    (*T)->data = data[i];
    (*T)->LTag = Link;
    (*T)->RTag = Link;
    if (i > *used)
        *used = i;
    order[i] = *T;
    if (lchildren[i] != 0)
    {
        BiThrTree l;
        CreateNode(&l, lchildren[i], data, lchildren, rchildren, order, used);
        (*T)->lchild = l;
    }
    else
        (*T)->lchild = NULL;
    if (rchildren[i] != 0)
    {
        BiThrTree r;
        CreateNode(&r, rchildren[i], data, lchildren, rchildren, order, used);
        (*T)->rchild = r;
    }
    else
        (*T)->rchild = NULL;
    return OK;
}

void PreThreading(BiThrTree p, BiThrTree *pre);
Status PreOrderThreading(BiThrTree *Thrt, BiThrTree T)
{
    *Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
    if (!(*Thrt))
        return ERROR;
    (*Thrt)->LTag = Link;
    BiThrTree tem = *Thrt;
    if (!T)
        (*Thrt)->lchild = *Thrt;
    else
    {
        (*Thrt)->lchild = T;
        BiThrTree *pre = &tem;
        PreThreading(T, pre);
    }
    return OK;
}

void PreThreading(BiThrTree p, BiThrTree *pre)
{
    if (p)
    {
        if (!p->lchild)
        {
            p->LTag = Thread;
            p->lchild = *pre;
        }
        *pre = p;
        if (p->LTag == Link)
            PreThreading(p->lchild, pre);
        if (p->RTag == Link)
            PreThreading(p->rchild, pre);
    }
}

void InThreading(BiThrTree p, BiThrTree *pre);
Status InOrderThreading(BiThrTree *Thrt, BiThrTree T)
{
    *Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
    if (!(*Thrt))
        return ERROR;
    (*Thrt)->LTag = Link;
    (*Thrt)->RTag = Thread;
    (*Thrt)->rchild = *Thrt;
    BiThrTree tem = *Thrt;
    if (!T)
        (*Thrt)->lchild = *Thrt;
    else
    {
        (*Thrt)->lchild = T;
        BiThrTree *pre = &tem;
        InThreading(T, pre);
        (*pre)->rchild = *Thrt;
        (*pre)->RTag = Thread;
        (*Thrt)->rchild = *pre;
    }
    return OK;
}

void InThreading(BiThrTree p, BiThrTree *pre)
{
    if (p)
    {
        InThreading(p->lchild, pre);
        if (!p->lchild)
        {
            p->LTag = Thread;
            p->lchild = *pre;
        }
        if (!(*pre)->rchild)
        {
            (*pre)->RTag = Thread;
            (*pre)->rchild = p;
        }
        *pre = p;
        InThreading(p->rchild, pre);
    }
}

void PostThreading(BiThrTree p, BiThrTree *pre, BiThrTree tem);
Status PostOrderThreading(BiThrTree *Thrt, BiThrTree T)
{
    *Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
    if (!(*Thrt))
        return ERROR;
    (*Thrt)->LTag = Link;
    (*Thrt)->RTag = Thread;
    (*Thrt)->rchild = *Thrt;
    BiThrTree tem = *Thrt;
    if (!T)
        (*Thrt)->lchild = *Thrt;
    else
    {
        (*Thrt)->lchild = T;
        BiThrTree *pre = &tem;
        PostThreading(T, pre, tem);
        if (!(*pre)->rchild)
        {
            (*pre)->rchild = *Thrt;
            (*pre)->RTag = Thread;
        }
        (*Thrt)->rchild = *pre;
    }
    return OK;
}

void PostThreading(BiThrTree p, BiThrTree *pre, BiThrTree tem)
{
    if (p)
    {
        PostThreading(p->lchild, pre, tem);
        PostThreading(p->rchild, pre, tem);
        if (!(*pre)->rchild)
        {
            (*pre)->RTag = Thread;
            (*pre)->rchild = p;
        }
        *pre = p;
    }
}

Status PrintPreorderLeft (BiThrTree Thrt, BiThrTree order[], int n)
{
    printf("%d ", Thrt->lchild->data);
    for(int i = 1; i <= n; i++)
    {
        if(order[i]->lchild != Thrt)
            printf("%d", order[i]->lchild->data);
        else    
            printf("0");
        if (i != n)
            printf(" ");
        else
            printf("\n");
        if (order[i]->LTag == Thread)
        {
            order[i]->LTag = Link;
            order[i]->lchild = NULL;
        }
    }
    return OK;
}

Status PrintPreorderRight (BiThrTree Thrt, BiThrTree order[], int n)
{
    printf("%d ", Thrt->lchild->data);
    for(int i = 1; i <= n; i++)
    {
        if(order[i]->rchild != NULL)
            printf("%d", order[i]->rchild->data);
        else    
            printf("0");
        if (i != n)
            printf(" ");
        else
            printf("\n");
    }
    return OK;
}

Status PrintInorderLeft (BiThrTree Thrt, BiThrTree order[], int n)
{
    printf("%d ", Thrt->lchild->data);
    for(int i = 1; i <= n; i++)
    {
        if(order[i]->lchild != Thrt)
            printf("%d", order[i]->lchild->data);
        else    
            printf("0");
        if (i != n)
            printf(" ");
        else
            printf("\n");
        if (order[i]->LTag == Thread)
        {
            order[i]->LTag = Link;
            order[i]->lchild = NULL;
        }
    }
    return OK;
}

Status PrintInorderRight (BiThrTree Thrt, BiThrTree order[], int n)
{
    printf("%d ", Thrt->lchild->data);
    for(int i = 1; i <= n; i++)
    {
        if(order[i]->rchild != Thrt)
            printf("%d", order[i]->rchild->data);
        else    
            printf("0");
        if (i != n)
            printf(" ");
        else
            printf("\n");
        if (order[i]->RTag == Thread)
        {
            order[i]->RTag = Link;
            order[i]->rchild = NULL;
        }
    }
    return OK;
}

Status PrintPostorderLeft (BiThrTree Thrt, BiThrTree order[], int n)
{
    printf("%d ", Thrt->lchild->data);
    for(int i = 1; i <= n; i++)
    {
        if(order[i]->lchild != NULL)
            printf("%d", order[i]->lchild->data);
        else    
            printf("0");
        if (i != n)
            printf(" ");
        else
            printf("\n");
    }
    return OK;
}

Status PrintPostorderRight (BiThrTree Thrt, BiThrTree order[], int n)
{
    printf("%d ", Thrt->lchild->data);
    for(int i = 1; i <= n; i++)
    {
        if(order[i]->rchild != Thrt)
            printf("%d", order[i]->rchild->data);
        else    
            printf("0");
        if (i != n)
            printf(" ");
        if (order[i]->RTag == Thread)
        {
            order[i]->RTag = Link;
            order[i]->rchild = NULL;
        }
    }
    return OK;
}