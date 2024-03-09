#include <stdio.h>
#include <malloc.h>

#define ERROR 0
#define OK 1

typedef int Status;
typedef int ElemType;
typedef struct queue
{
    ElemType *base;
    int front;
    int rear;
} CircularQueue;

Status InitQueue (CircularQueue *cq, int n);
Status Enqueue (CircularQueue *cq, ElemType e, int n);
Status Dequeue (CircularQueue *cq, ElemType *e, int n);

int main()
{
    CircularQueue Q;
    int n;
    ElemType c;
    char check;

    scanf("%d", &n);
    InitQueue(&Q, n);

    n = n + 1;

    getchar();
    scanf("%d", &c);
    Enqueue(&Q, c, n);

    while ((check = getchar()) == ',')
    {
        scanf("%d", &c);
        Enqueue(&Q, c, n);
    }

    for (int i = 0 ; i < n - 1; i++)
        if (i < n-2)
        {
            Dequeue(&Q, &c, n);
            printf("%d,", c);
        }
        else
        {
            Dequeue(&Q, &c, n);
            printf("%d", c);
        }
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