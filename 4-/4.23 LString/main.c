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
} Chunk;

typedef struct 
{
    Chunk *head;
    Chunk *tail;
    int curLen;
}LString;

void InitLString(LString *L);
void CreateLString(LString *L, int n);
void ReverseLString(LString *L);
int SymmetryLstring(LString *L, int n);

int main()
{
    LString L;
    int n, check;
    char c;
    Chunk* p;

    scanf("%d", &n);
    getchar();

    InitLString(&L);
    CreateLString(&L, n);

    p = L.head;
    while ((c = getchar()) != '\n')
    {
        p->ch[0] = c;
        p = p->next;
    }

    check = SymmetryLstring(&L, n);
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
    L->curLen = 1;
    for (int i = 0; i < n-1; i++)
    {
        c = (Chunk *)malloc(sizeof(Chunk));
        c->ch[0] = '\0';
        c->next = L->head;
        L->head = c;
        L->curLen++;
    }
}

void ReverseLString(LString *L)
{
    Chunk *m, *n, *p;

    m = L->head;
    p = L->head->next;
    n = L->head->next;
    L->head = L->tail;
    L->tail = m;

    for (int i = 0; n; i++)
    {
        p = n->next;
        n->next = m;
        m = n;
        n = p;
    }
}

int SymmetryLstring(LString *L, int n)
{
    LString p, q;
    Chunk *a, *b, *c;

    InitLString(&p);
    InitLString(&q);
    CreateLString(&p, n/2);
    CreateLString(&q, n/2);

    a = p.head;
    b = q.head;
    c = L->head;

    for (int i = 0; i < n/2; i++)
    {
        a->ch[0] = c->ch[0];
        a = a->next;
        c = c->next;
    }
    if (L->curLen % 2)
        c = c->next;
    for (int i = 0; i < n/2; i++)
    {
        b->ch[0] = c->ch[0];
        b = b->next;
        c = c->next;
    }

    ReverseLString(&q);
    a = p.head;
    b = q.head;

    for (int i = 0; i < n/2; i++)
    {
        if (a->ch[0] != b->ch[0])
            return ERROR;
        a = a->next;
        b = b->next;
    }
    return OK;
}