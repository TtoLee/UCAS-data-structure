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

Status CreateBiThrTree(BiThrTree *T, BiThrTree *p, int flag);
Status CreateNode(BiThrTree *T, int i, TElemType data[], int lchildren[], int rchildren[], TElemType p_data, BiThrTree *p);
Status InOrderThreading(BiThrTree *Thrt, BiThrTree T);;
void InsertTree(BiThrTree *p, BiThrTree *q);
Status PrintElement(TElemType e);
Status InorderTraverse (BiThrTree T, Status (*Visit)(TElemType e));

int main()
{
    BiThrTree T, p, x, Thrt;
    int u, v;

    CreateBiThrTree(&T, &p, 1);
    CreateBiThrTree(&x, &p, 0);
    InsertTree(&T, &x);
    InOrderThreading(&Thrt, T);
    InorderTraverse(Thrt, PrintElement);
}

Status CreateBiThrTree(BiThrTree *T, BiThrTree *p, int flag)
{
    int lchildren[MAX_TREE_SIZE], rchildren[MAX_TREE_SIZE], n;
    TElemType t, data[MAX_TREE_SIZE], p_data;
    char c;
    n = 0;

    scanf("%d", &t);
    lchildren[0] = t;
    while ((c=getchar()) != '\n')
    {
        scanf("%d", &t);
        if (t != 0)
            lchildren[++n] = t - lchildren[0] + 1;
        else
            lchildren[++n] = 0;
    }
    for (int i = 0; i <= n; i++)
    {
        scanf("%d", &t);
        if (t != 0)
            rchildren[i] = t - lchildren[0] + 1;
        else
            rchildren[i] = 0;
        data[i] = i + lchildren[0] - 1;
    }
    lchildren[0] = 1;
    
    if (flag)
        scanf("%d", &p_data);
    else
        p_data = 0;
    CreateNode(T, 1, data, lchildren, rchildren, p_data, p);
    return OK;
}

Status CreateNode(BiThrTree *T, int i, TElemType data[], int lchildren[], int rchildren[], TElemType p_data, BiThrTree *p)
{
    *T = (BiThrTree)malloc(sizeof(BiThrNode));
    if (!(*T))
        return ERROR;
    (*T)->data = data[i];
    (*T)->LTag = Link;
    (*T)->RTag = Link;
    if (p_data == data[i])
        *p = *T;
    if (lchildren[i] != 0)
    {
        BiThrTree l;
        CreateNode(&l, lchildren[i], data, lchildren, rchildren, p_data, p);
        (*T)->lchild = l;
    }
    else
        (*T)->lchild = NULL;
    if (rchildren[i] != 0)
    {
        BiThrTree r;
        CreateNode(&r, rchildren[i], data, lchildren, rchildren, p_data, p);
        (*T)->rchild = r;
    }
    else
        (*T)->rchild = NULL;
    return OK;
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
    if (!T)
        (*Thrt)->lchild = *Thrt;
    else
    {
        (*Thrt)->lchild = T;
        BiThrTree *pre = Thrt;
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

void InsertTree(BiThrTree *p, BiThrTree *q)
{
    if (!(*p)->lchild)
        (*p)->lchild = *q;
    else
    {
        BiThrTree t = (*p)->lchild;
        (*p)->lchild = *q;
        (*q)->rchild = t;
    }
}

Status PrintElement(TElemType e)
{
    printf("%d ", e);
    return OK;
}

Status InorderTraverse (BiThrTree T, Status (*Visit)(TElemType e))
{
    BiThrTree p = T->lchild;
    while (p != T)
    {
        while (p->LTag == Link)
            p = p->lchild;
        if (!Visit(p->data))
            return ERROR;
        while (p->RTag == Thread && p->rchild != T)
        {
            p = p->rchild;
            Visit(p->data);
        }
        p = p->rchild;
    }
    Visit(p->data);
    return OK;
}