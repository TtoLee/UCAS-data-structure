#include <stdio.h>
#include <malloc.h>

#define MAX_TREE_SIZE 100
#define ERROR 0
#define OK 1 
#define INITSIZE 100
#define INCREMENTSIZE 10

typedef int Status;
typedef char TElemType;
typedef struct 
{
    TElemType *top;
    TElemType *base;
    int stacksize;
} Sqstack;
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

Status CreateBiTree(BiTree *T, TElemType data[], int lchildren[], int rchildren[]);
Status CreateNode(BiTree *T, int i, TElemType data[], int lchildren[], int rchildren[]);
Status PrintElement(TElemType e);
Status PreOrderTraverse (BiTree T, Status (* visit)(TElemType e));
Status Initstack (Sqstack *s);
Status Push (Sqstack *s, TElemType *e);
Status Pop (Sqstack *s, TElemType *e);
Status Empty (Sqstack s);

int main()
{
    TElemType tree[MAX_TREE_SIZE];
    char c;
    int Lchildren[MAX_TREE_SIZE], Rchildren[MAX_TREE_SIZE];
    int n = 0;
    Sqstack S;
    BiTree T;

    while ((c = getchar()) != EOF)
    {
        n++;
        tree[n] = c;
        scanf("%d %d", &Lchildren[n], &Rchildren[n]);
        getchar();
    }
    CreateBiTree(&T, tree, Lchildren, Rchildren);
    PreOrderTraverse(T, PrintElement);
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
    if (lchildren[i] != -1)
    {
        BiTree l;
        CreateNode(&l, lchildren[i], data, lchildren, rchildren);
        (*T)->lchild = l;
    }
    else
        (*T)->lchild = NULL;
    if (rchildren[i] != -1)
    {
        BiTree r;
        CreateNode(&r, rchildren[i], data, lchildren, rchildren);
        (*T)->rchild = r;
    }
    else
        (*T)->rchild = NULL;
    return OK;
}

Status PrintElement(TElemType e)
{
    printf("%c ", e);
    return OK;
}

Status PreOrderTraverse (BiTree T, Status (* visit)(TElemType e))
{
    if (T)
    {
        if (visit(T->data))
            if (PreOrderTraverse(T->lchild, visit))
                if (PreOrderTraverse(T->rchild, visit))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

Status Initstack (Sqstack *s)
{
    s->base = (TElemType *)malloc(INITSIZE * sizeof(TElemType));
    if (!s)
        return ERROR;
    s->top = s->base;
    s->stacksize = INITSIZE;
    return OK;   
}

Status Push (Sqstack *s, TElemType *e)
{
    if (s->top >= s->base + s->stacksize)
    {
        s->base = (TElemType *)realloc(s->base, (s->stacksize + INCREMENTSIZE) * sizeof(TElemType));
        if (!s->base)
            return ERROR;
        s->stacksize += INCREMENTSIZE;
    }
    *(s->top) = *e;
    s->top++;
    return OK;
}

Status Pop (Sqstack *s, TElemType *e)
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

Status Empty (Sqstack s)
{
    if (s.top == s.base)
        return 1;
    else 
        return 0;
}