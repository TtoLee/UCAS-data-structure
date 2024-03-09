#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 30
#define ERROR 0
#define OK 1
#define INITSIZE 100
#define INCREMENTSIZE 10

typedef char ElemType;
typedef int SElemType;
typedef int InfoType;
typedef int Status;
typedef enum {DG, UDG, DN, UDN} GraphKind;
typedef struct LinkNode
{
    int adjvex;
    InfoType *info;
    struct LinkNode *nextarc;
} LinkNode;
typedef struct VexNode
{
    ElemType data;
    int indegree;
    LinkNode *firstarc;
} VexNode;
typedef struct ALGraph
{
    GraphKind kind;
    int vexnum, arcnum;
    VexNode AdjList[MAX_VERTEX_NUM];
} ALGraph;
typedef struct 
{
    SElemType *top;
    SElemType *base;
    int stacksize;
} Sqstack;

Status CreateGraph(ALGraph *G);
Status AddVertex(int v, ALGraph *G);
Status AddArc(int m, int n, ALGraph *G);
Status TopologicalSort(ALGraph G, Sqstack *M);
Status Initstack (Sqstack *s);
Status Push (Sqstack *s, SElemType *e);
Status Pop (Sqstack *s, SElemType *e);
int Empty (Sqstack s);

int main()
{
    int v, m, n;
    char c;
    ALGraph G;
    Sqstack M;

    scanf("%d", &v);
    getchar();
    CreateGraph(&G);
    AddVertex(v, &G);
    for (int i = 0; i < v; i++)
    {
        c = getchar();
        G.AdjList[i].data = c;
        if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            scanf("%d %d", &m, &n);
            AddArc(i, n, &G);
            AddArc(i, m, &G);
        }
        getchar();
    }
    Initstack(&M);
    TopologicalSort(G, &M);
    while (!Empty(M))
    {
        Pop(&M, &m);
        printf("%c", G.AdjList[m].data);
    }

}

Status CreateGraph(ALGraph *G)
{
    G->kind = DG;
    G->vexnum = 0;
    G->arcnum = 0;
    return OK;
}

Status AddVertex(int v, ALGraph *G)
{
    if (v > MAX_VERTEX_NUM) 
        return ERROR;
    for (int i = 0; i < v; i++)
    {
        G->vexnum++;
        G->AdjList[i].firstarc = NULL;
        G->AdjList[i].indegree = 0;
    }
    return OK;
}

Status AddArc(int m, int n, ALGraph *G)
{
    LinkNode *p, *q;
    VexNode *v;
    v = &(G->AdjList[m]);
    q = (LinkNode*)malloc(sizeof(LinkNode));
    q->adjvex = n;
    q->nextarc = NULL;
    
    if (!(*v).firstarc)
        (*v).firstarc = q;
    else
    {
        p = (*v).firstarc;
        while (p->nextarc)
            p = p->nextarc;
        q->nextarc = p->nextarc;
        p->nextarc = q;
    }
    G->AdjList[n].indegree++;
    return OK;
}

Status TopologicalSort(ALGraph G, Sqstack *M)
{
    Sqstack S;
    int e;
    LinkNode *p;
    Initstack(&S);
    for (int i = 0; i < G.vexnum; i++)
        if (G.AdjList[i].indegree ==  0)
            Push(&S, &i);
    int count = 0;
    while (!Empty(S))
    {
        Pop(&S, &e);
        Push(M, &e);
        count++;
        for (p = G.AdjList[e].firstarc; p; p = p->nextarc)
        {
            int k = p->adjvex;
            G.AdjList[k].indegree--;
            if (G.AdjList[k].indegree == 0)
                Push(&S, &k);
        }
    }
    return OK;
}

Status Initstack (Sqstack *s)
{
    s->base = (SElemType *)malloc(INITSIZE * sizeof(SElemType));
    if (!s)
        return ERROR;
    s->top = s->base;
    s->stacksize = INITSIZE;
    return OK;   
}

Status Push (Sqstack *s, SElemType *e)
{
    if (s->top >= s->base + s->stacksize)
    {
        s->base = (SElemType *)realloc(s->base, (s->stacksize + INCREMENTSIZE) * sizeof(SElemType));
        if (!s->base)
            return ERROR;
        s->stacksize += INCREMENTSIZE;
    }
    *(s->top) = *e;
    s->top++;
    return OK;
}

Status Pop (Sqstack *s, SElemType *e)
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

int Empty (Sqstack s)
{
    if (s.top == s.base)
        return 1;
    else 
        return 0;
}