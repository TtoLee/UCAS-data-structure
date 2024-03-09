#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 100
#define INCREMENTSIZE 10
#define MAX_TREE_SIZE 100
#define ERROR 0
#define OK 1 

typedef int Status;
typedef char TElemType;
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
typedef BiTree ElemType;
typedef struct 
{
    ElemType *top;
    ElemType *base;
    int stacksize;
} Sqstack;

Status CreateBiTree(BiTree *T);
Status CreateNode(BiTree *T, int n, TElemType preorder[], TElemType inorder[], Sqstack *S);
Status PrintElement(TElemType e);
Status PostOrderTraverse (BiTree T, Status (* visit)(TElemType e));
Status Initstack (Sqstack *s);
Status Push (Sqstack *s, ElemType *e);
Status Pop (Sqstack *s, ElemType *e);
Status Empty (Sqstack s);
Status GetTop (Sqstack *s, ElemType *e);

int main()
{
    BiTree T;
    CreateBiTree(&T);
    PostOrderTraverse(T, PrintElement);
}

Status CreateBiTree(BiTree *T)
{
    TElemType c, preorder[MAX_TREE_SIZE], inorder[MAX_TREE_SIZE];
    int n = 0;
    Sqstack S;

    while ((c = getchar()) != '\n')
        preorder[++n] = c;
    n = 0;
    while ((c = getchar()) != '\n')
        inorder[++n] = c;
    
    Initstack (&S);
    CreateNode(T, n, preorder, inorder, &S);
}

Status CreateNode(BiTree *T, int n, TElemType preorder[], TElemType inorder[], Sqstack *S)
{
    int i, j;
    i = j = 1;
    *T = (BiTree)calloc(1, sizeof(BiTNode));
    if (!(*T))
        return ERROR;
    (*T)->data = preorder[i];
    Push(S, T);
    
    while (!Empty(*S))
    {
        BiTree M;
        GetTop(S, &M);
        if (M->data != inorder[j])
        {
            BiTree N;
            N = (BiTree)calloc(1, sizeof(BiTNode));
            N->data = preorder[++i];
            M->lchild = N;
            Push(S, &N);
        }
        else if (M->data == inorder[j])
        {
            BiTree N, L;
            GetTop(S, &L);
            while (L->data == inorder[j])
            {
                j++;
                Pop(S, &M);
                GetTop(S, &L);
                if (j == n + 1)
                    break;
            }
            if (j == n + 1)
                break;
            N = (BiTree)calloc(1, sizeof(BiTNode));
            N->data = preorder[++i];
            M->rchild = N;
            Push(S, &N);
        }
    }

    return OK;
}

Status Initstack (Sqstack *s)
{
    s->base = (ElemType *)malloc(INITSIZE * sizeof(ElemType));
    if (!s)
        return ERROR;
    s->top = s->base;
    s->stacksize = INITSIZE;
    return OK;   
}

Status PrintElement(TElemType e)
{
    printf("%c", e);
    return OK;
}

Status PostOrderTraverse (BiTree T, Status (* visit)(TElemType e))
{
    if (T)
    {
        if (PostOrderTraverse(T->lchild, visit))
            if (PostOrderTraverse(T->rchild, visit))
                if (visit(T->data))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

Status Push (Sqstack *s, ElemType *e)
{
    if (s->top >= s->base + s->stacksize)
    {
        s->base = (ElemType *)realloc(s->base, (s->stacksize + INCREMENTSIZE) * sizeof(ElemType));
        if (!s->base)
            return ERROR;
        s->stacksize += INCREMENTSIZE;
    }
    *(s->top) = *e;
    s->top++;
    return OK;
}

Status Pop (Sqstack *s, ElemType *e)
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

Status GetTop (Sqstack *s, ElemType *e)
{
    if (s->top == s->base)
        return ERROR;
    *e = *(s->top - 1);
    return OK;
}