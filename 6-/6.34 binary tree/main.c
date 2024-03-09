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
    struct BiTNode *parent, *lchild, *rchild;
}BiTNode, *BiTree;

Status CreateBiTree(BiTree *T, BiTree order[]);
Status CreateNode(BiTree *T, int i, TElemType data[], int parent[], int lchildren[], int rchildren[], BiTree order[]);
Status CheckSon(BiTree u, BiTree v);

int main()
{
    BiTree T, order[MAX_TREE_SIZE];
    int u, v;

    CreateBiTree(&T, order);
    scanf("%d %d", &u, &v);
    int check = CheckSon(order[u], order[v]);
    printf("%d", check);
}

Status CreateBiTree(BiTree *T, BiTree order[])
{
    int lchildren[MAX_TREE_SIZE], rchildren[MAX_TREE_SIZE], parent[MAX_TREE_SIZE], n;
    TElemType t, data[MAX_TREE_SIZE];
    char c;
    n = 0;

    scanf("%d", &t);
    parent[1] = t;
    while ((c=getchar()) != '\n')
    {
        scanf("%d", &t);
        parent[++n] = t;
    }
    for(int i = 0; i <= n; i++)
    {
        scanf("%d", &t);
        lchildren[i] = t;
        data[i] = i;
    }
    for (int i = 0; i <= n; i++)
    {
        scanf("%d", &t);
        rchildren[i] = t;
    }

    CreateNode(T, 1, data, parent, lchildren, rchildren, order);
}

Status CreateNode(BiTree *T, int i, TElemType data[], int parent[], int lchildren[], int rchildren[], BiTree order[])
{
    *T = (BiTree)malloc(sizeof(BiTNode));
    if (!(*T))
        return ERROR;
    (*T)->data = data[i];
    (*T)->parent = order[parent[i]];
    order[i] = *T;
    if (lchildren[i] != 0)
    {
        BiTree l;
        CreateNode(&l, lchildren[i], data, parent, lchildren, rchildren, order);
        (*T)->lchild = l;
    }
    else
        (*T)->lchild = NULL;
    if (rchildren[i] != 0)
    {
        BiTree r;
        CreateNode(&r, rchildren[i], data, parent, lchildren, rchildren, order);
        (*T)->rchild = r;
    }
    else
        (*T)->rchild = NULL;
    return OK;
}

Status CheckSon(BiTree u, BiTree v)
{
    if (v == u)
        return 1;
    if (v->lchild)
        if (CheckSon(u, v->lchild))
            return 1;
    if (v->rchild)
        if (CheckSon(u, v->rchild))
            return 1;

    return 0;
}