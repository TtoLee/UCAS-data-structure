#include <stdio.h>
#include <malloc.h>

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
typedef struct queue
{
    ElemType *base;
    int front;
    int rear;
} CircularQueue;

Status CreateBiTree(BiTree *T);
Status CreateNode(BiTree *T, int i, TElemType data[], int lchildren[], int rchildren[]);
void LevelTraverse(BiTree T, CircularQueue *Q);
Status CheckCompleteTree(BiTree T);
Status InitQueue (CircularQueue *cq, int n);
Status QueueEmpty (CircularQueue Q);
Status Enqueue (CircularQueue *cq, ElemType e, int n);
Status Dequeue (CircularQueue *cq, ElemType *e, int n);

int main()
{
    BiTree T;

    CreateBiTree(&T);
    int check = CheckCompleteTree(T);
    if (check == 1)
        printf("Yes");
    else
        printf("No");
}

Status CreateBiTree(BiTree *T)
{
    char c;
    int n = 0;
    int Lchildren[MAX_TREE_SIZE], Rchildren[MAX_TREE_SIZE];
    TElemType data[MAX_TREE_SIZE];

    while ((c = getchar()) != EOF)
    {
        n++;
        data[n] = c;
        scanf("%d %d", &Lchildren[n], &Rchildren[n]);
        getchar();
    }
    CreateNode(T, 1, data, Lchildren, Rchildren);
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

void LevelTraverse(BiTree T, CircularQueue *Q)
{
    CircularQueue Tem;
    InitQueue(&Tem, MAX_TREE_SIZE);
    BiTree p;

    Enqueue(&Tem, T, MAX_TREE_SIZE);
    while (!QueueEmpty(Tem))
    {
        Dequeue(&Tem, &p, MAX_TREE_SIZE);
        Enqueue(Q, p, MAX_TREE_SIZE);
        if(p->lchild)
            Enqueue(&Tem, p->lchild, MAX_TREE_SIZE);
        if (p->rchild)
            Enqueue(&Tem, p->rchild, MAX_TREE_SIZE);
    }
}

Status CheckCompleteTree(BiTree T)
{
    CircularQueue Q;
    InitQueue(&Q, MAX_TREE_SIZE);
    LevelTraverse(T, &Q);
    BiTree p;
    int flag = 1;
    while (!QueueEmpty(Q))
    {
        Dequeue(&Q, &p, MAX_TREE_SIZE);
        if (!p->lchild && flag)
            flag = 0;
        else if (p->lchild && !flag)
            return 0;
        if (!p->rchild && flag)
            flag = 0;
        else if (p->rchild && !flag)
            return 0;
    }
    return 1;
}

Status InitQueue (CircularQueue *cq, int n)
{
    cq->base = (ElemType *)malloc(n*sizeof(ElemType));
    if (!cq->base)
        return ERROR;
    cq->front = 0;
    cq->rear = 0;
    return OK;
}

Status QueueEmpty (CircularQueue Q)
{
    if (Q.front == Q.rear)
        return 1;
    return 0;
}

Status Enqueue (CircularQueue *cq, ElemType e, int n)
{
    if((cq->rear+1) % n == cq->front)
        return ERROR;
    cq->base[cq->rear] = e;
    cq->rear = (cq->rear+1) % n;
    return OK;
}

Status Dequeue (CircularQueue *cq, ElemType *e, int n)
{
    if (cq->front == cq->rear)
        return ERROR;
    *e = cq->base[cq->front];
    cq->front = (cq->front + 1) % n;
}