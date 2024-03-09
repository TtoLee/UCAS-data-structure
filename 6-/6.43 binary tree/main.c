#include <stdio.h>
#include <malloc.h>

#define MAX_TREE_SIZE 100
#define ERROR 0
#define OK 1 

typedef int Status;
typedef int TElemType;
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

Status CreateBiTree(BiTree *T, TElemType data[], int lchildren[], int rchildren[]);
Status CreateNode(BiTree *T, int i, TElemType data[], int lchildren[], int rchildren[]);
Status PrintBiTree(BiTree T, int n, TElemType lchildren[], TElemType rchildren[]);
Status ReverseBiTree(BiTree *T);

int main()
{
    BiTree T;
    int lchildren[MAX_TREE_SIZE], rchildren[MAX_TREE_SIZE], n;
    TElemType child, data[MAX_TREE_SIZE];
    char c;
    n = 0;

    scanf("%d", &child);
    lchildren[0] = child;
    while ((c=getchar()) != '\n')
    {
        scanf("%d", &child);
        lchildren[++n] = child;
    }
    for(int i = 0; i <= n; i++)
    {
        scanf("%d", &child);
        rchildren[i] = child;
        data[i] = i;
    }

    CreateBiTree(&T, data, lchildren, rchildren);
    ReverseBiTree(&T);
    for (int i = 0; i <= n; i++)
    {
        lchildren[i] = 0;
        rchildren[i] = 0;
    }

    lchildren[0] = T->data;
    rchildren[0] = T->data;
    PrintBiTree(T, n, lchildren, rchildren);
}

Status CreateBiTree(BiTree *T, TElemType data[], int lchildren[], int rchildren[])
{
    CreateNode(T, 1, data, lchildren, rchildren);
}

Status CreateNode(BiTree *T, int i, TElemType data[], int lchildren[], int rchildren[])
{
    *T = (BiTree)malloc(sizeof(BiTNode));
    if (!(*T))
        return ERROR;
    (*T)->data = data[i];
    if (lchildren[i] != 0)
    {
        BiTree l;
        CreateNode(&l, lchildren[i], data, lchildren, rchildren);
        (*T)->lchild = l;
    }
    else
        (*T)->lchild = NULL;
    if (rchildren[i] != 0)
    {
        BiTree r;
        CreateNode(&r, rchildren[i], data, lchildren, rchildren);
        (*T)->rchild = r;
    }
    else
        (*T)->rchild = NULL;
    return OK;
}

Status InitTreeArray(BiTree T, TElemType lchildren[], TElemType rchildren[]);
Status PrintBiTree(BiTree T, int n, TElemType lchildren[], TElemType rchildren[])
{
    for (int i = 0; i <= n; i++)
    {
        lchildren[i] = 0;
        rchildren[i] = 0;
    }

    lchildren[0] = T->data;
    rchildren[0] = T->data;
    InitTreeArray(T, lchildren, rchildren);
    for (int i = 0; i <= n; i++)
    {
        if (i != n)
            printf("%d ", lchildren[i]);
        else
            printf("%d\n", lchildren[i]);
    }
    for (int i = 0; i <= n; i++)
    {
        if (i != n)
            printf("%d ", rchildren[i]);
        else
            printf("%d", rchildren[i]);
    }
}

Status InitTreeArray(BiTree T, TElemType lchildren[], TElemType rchildren[])
{
    if (T)
    {
        if (T->lchild)
            lchildren[T->data] = T->lchild->data;
        if (T->rchild)
            rchildren[T->data] = T->rchild->data;
        InitTreeArray(T->lchild, lchildren, rchildren);
        InitTreeArray(T->rchild, lchildren, rchildren);
        return OK;
    }
    else 
        return OK;
}

Status ReverseBiTree(BiTree *T)
{
    if ((*T)->lchild || (*T)->rchild)
    {
        BiTree temp;
        temp = (*T)->lchild;
        (*T)->lchild = (*T)->rchild;
        (*T)->rchild = temp;
        if ((*T)->lchild)
            ReverseBiTree(&(*T)->lchild);
        if ((*T)->rchild)
            ReverseBiTree(&(*T)->rchild);
    }
    return OK;
}