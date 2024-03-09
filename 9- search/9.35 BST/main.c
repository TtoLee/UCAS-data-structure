#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

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
typedef BiTree ElemType;
typedef struct queue
{
    ElemType *base;
    int front;
    int rear;
} CircularQueue;

Status CreateBiTree(BiTree *T);
Status CreateNode(BiTree *T, int n, TElemType data[]);
Status SearchBFS(BiTree T, TElemType key, BiTree f, BiTree *p);
Status PrintTarget(BiTree T, int min, int max);

int main()
{
    BiTree T = NULL;
    int min, max;

    CreateBiTree(&T);
    scanf("%d\n%d", &min, &max);
    PrintTarget(T, min, max);
}

Status CreateBiTree(BiTree *T)
{
    char c = ' ';
    int n = 0;
    TElemType data[MAX_TREE_SIZE];

    while (c != '\n')
    {
        scanf("%d", &data[n]);
        n++;
        c = getchar();
    }
    int tem = data[0];
    data[0] = data [n / 2];
    data[n / 2] = tem;
    CreateNode(T, n, data);
}

Status CreateNode(BiTree *T, int n, TElemType data[])
{
    BiTree p, s;
    int insert_data;
    for (int i = 0; i < n; i++)
    {
        insert_data = data[i];
        if (!SearchBFS(*T, insert_data, NULL, &p))
        {
            s = (BiTree)malloc(sizeof(BiTNode));
            s->data = insert_data;
            s->lchild = NULL;
            s->rchild = NULL;
            if (!p)
                *T = s;
            else if (insert_data < p->data)
                p->lchild = s;
            else
                p->rchild = s;
        }
        else
            return ERROR;
    }
    return OK;
}

Status SearchBFS(BiTree T, TElemType key, BiTree f, BiTree *p)
{
    if (!T)
    {
        *p = f;
        return ERROR;
    }
    else if (key == T->data)
    {
        p = &T;
        return OK;
    }
    else if (key < T->data)
        return SearchBFS(T->lchild, key, T, p);
    else
        return SearchBFS(T->rchild, key, T, p);
}

Status PrintTarget(BiTree T, int min, int max)
{
    if (!T)
        return OK;

    if (T->data > min)
        PrintTarget(T->lchild, min, max);
    if (T->data > min && T->data < max)
        printf("%d ", T->data);
    if (T->data < max)
        PrintTarget(T->rchild, min, max);
    return OK;
}