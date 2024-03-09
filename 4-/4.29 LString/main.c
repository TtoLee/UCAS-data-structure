#include <stdio.h>
#include <malloc.h>

#define INITSTRLEN 100
#define ERROR 0
#define OK 1
#define MaxSize 500
#define CHUNKSIZE 1

typedef struct Chunk
{
    char ch[CHUNKSIZE];
    struct Chunk *next;
    struct Chunk *succ;
} Chunk;

typedef struct 
{
    Chunk *head;
    Chunk *tail;
    int curLen;
}LString;

void InitLString(LString *L);
void CreateLString(LString *L, int n);
int index_kmp(LString S, LString T);
void GetNext(LString *S);

int main()
{
    LString S, T;
    int m, n, check;
    char c;
    Chunk *p, *q;

    scanf("%d", &m);
    scanf("%d", &n);
    getchar();

    InitLString(&S);
    InitLString(&T);
    CreateLString(&S, m);
    CreateLString(&T, n);

    p = S.head;
    q = T.head;
    while ((c = getchar()) != '\n')
    {
        p = p->next;
        p->ch[0] = c;
    }
    while ((c = getchar()) != '\n')
    {
        q = q->next;
        q->ch[0] = c;
    }

    GetNext(&T);
    check = index_kmp(S, T);
    printf("%d", check);
}

void InitLString(LString *L)
{
    L = (LString *)malloc(sizeof(LString));
    L->curLen = 0;
}

void CreateLString(LString *L, int n)
{
    Chunk *c;
    c = (Chunk *)malloc(sizeof(Chunk));
    c->ch[0] = '\0';
    c->next = NULL;
    L->head = c;
    L->tail = c;
    L->curLen = 0;
    for (int i = 0; i < n; i++)
    {
        c = (Chunk *)malloc(sizeof(Chunk));
        c->ch[0] = '\0';
        c->next = L->head;
        L->head = c;
        L->curLen++;
    }
}

int index_kmp(LString S, LString T)
{
    Chunk *p, *q, *r;
    int order;
    p = S.head->next;
    q = T.head->next;

    while (p && q)
    {
        if(q == T.head || p->ch[0] == q->ch[0])
        {
            p = p->next;
            q = q->next;
        }
        else
            q = q->succ;
    }

    if (!q)
    {
        r = S.head->next;
        for (order = 0; r != p; order++)
            r = r->next;
        return order - T.curLen;
    }
    else
        return -1;   
}

void GetNext(LString *T)
{
    Chunk *p, *q, *r;

    p = T->head->next;
    p->succ = T->head;
    q = T->head;

    while (p->next)
    {
        if (q == T->head || p->ch[0] == q->ch[0])
        {
            p = p->next;
            q = q->next;
            p->succ = q;
        }
        else
            q = q->succ;
    }
}