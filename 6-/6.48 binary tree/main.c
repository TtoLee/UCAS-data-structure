#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100
#define ERROR 0
#define OK 1 

typedef int Status;
typedef char TElemType;
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *parent, *lchild, *rchild;
}BiTNode, *BiTree;
typedef struct queue
{
    TElemType *base;
    int front;
    int rear;
} CircularQueue;

Status CreateBiTree(BiTree *T, BiTree *p, BiTree *q);   //与下面一个函数是创造树的
Status CreateNode(BiTree *T, int i, CircularQueue *data, CircularQueue *tree, TElemType p_data, TElemType q_data, BiTree *p, BiTree *q);//创造树的同时寻找确定p,a是哪个节点
Status CheckSon(BiTree u, BiTree v);    //判断v是不是u的祖先
TElemType FindAncestor(BiTree p, BiTree q); //寻找最近共同祖先
Status InitQueue (CircularQueue *cq, int n);    //初始化队列
Status Enqueue (CircularQueue *cq, TElemType e, int n); //入队列
Status Dequeue (CircularQueue *cq, TElemType *e, int n); //出队列

int main()
{
    BiTree T, p, q;
    TElemType ancestor;

    CreateBiTree(&T, &p, &q);
    ancestor = FindAncestor(p, q);
    printf("%c", ancestor);
    return 0;
}

Status CreateBiTree(BiTree *T, BiTree *p, BiTree *q)
{
    TElemType p_data, q_data;
    CircularQueue tree, data;
    int n, i;
    char c;
    n = i = 0;

    InitQueue(&tree, 2 * MAX_TREE_SIZE + 3);
    InitQueue(&data, MAX_TREE_SIZE);

    while ((c=getchar()) != '\n')
    {
        Enqueue(&tree, c, 2 * MAX_TREE_SIZE + 3);
        if (c != '^')
            Enqueue(&data, c, MAX_TREE_SIZE);
    }

    scanf("%c %c", &p_data, &q_data);
    CreateNode(T, 1, &data, &tree, p_data, q_data, p, q);
}

Status CreateNode(BiTree *T, int i, CircularQueue *data, CircularQueue *tree, TElemType p_data, TElemType q_data, BiTree *p, BiTree *q)
{
    TElemType c, d;

    *T = (BiTree)calloc(1, sizeof(BiTNode));
    if (!(*T))
        return ERROR;
    Dequeue(data, &d, MAX_TREE_SIZE);
    (*T)->data = d;
    if (d == p_data)
        *p = *T;
    if (d == q_data)
        *q = *T;
    if (i == 1)
    {
        Dequeue(tree, &c, 2 * MAX_TREE_SIZE + 3);
        (*T)->parent = NULL;
        i = 0;
    }

    if (Dequeue(tree, &c, 2 * MAX_TREE_SIZE + 3))
    {
        if (c != '^')
        {
            BiTree L;
            CreateNode(&L, i, data, tree, p_data, q_data, p, q);
            (*T)->lchild = L;
            L->parent = *T;
        }
        else
            (*T)->lchild = NULL;
    }
    if (Dequeue(tree, &c, 2 * MAX_TREE_SIZE + 3))
    {
        if (c != '^')
        {
            BiTree L;
            CreateNode(&L, i, data, tree, p_data, q_data, p, q);
            (*T)->rchild = L;
            L->parent = *T;
        }
        else
            (*T)->rchild = NULL;
    }
    return OK;
}

TElemType FindOtherAncestor(BiTree p, BiTree q);

TElemType FindAncestor(BiTree p, BiTree q)
{
    if (CheckSon(p, q))
    {
        if (!q->parent)
            return q->data;
        return q->parent->data;
    }
    if (CheckSon(q, p))
    {
        if (!p->parent)
            return p->data;
        return p->parent->data;
    }
    return FindOtherAncestor (p->parent, q);
}

TElemType FindOtherAncestor(BiTree p, BiTree q)
{
    if (CheckSon(p, q))
        return q->data;
    if (CheckSon(q, p))
        return p->data;
    return FindOtherAncestor (p->parent, q);
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

Status InitQueue (CircularQueue *cq, int n)
{
    cq->base = (TElemType *)malloc(n*sizeof(TElemType));
    if (!cq->base)
        return ERROR;
    cq->front = 0;
    cq->rear = 0;
    return OK;
}

Status Enqueue (CircularQueue *cq, TElemType e, int n)
{
    if((cq->rear+1) % n == cq->front)
        return ERROR;
    cq->base[cq->rear] = e;
    cq->rear = (cq->rear+1) % n;
    return OK;
}

Status Dequeue (CircularQueue *cq, TElemType *e, int n)
{
    if (cq->front == cq->rear)
        return ERROR;
    *e = cq->base[cq->front];
    cq->front = (cq->front + 1) % n;
    return OK;
}
