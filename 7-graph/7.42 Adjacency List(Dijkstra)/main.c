#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTEX_NUM 30
#define ERROR 0
#define OK 1
#define INITSIZE 100
#define INCREMENTSIZE 10

typedef int ElemType;
typedef int SElemType;
typedef int InfoType;
typedef int Status;
typedef enum {DG, UDG, DN, UDN} GraphKind;
typedef struct LinkNode
{
    int adjvex;
    InfoType info;
    struct LinkNode *nextarc;
} LinkNode;
typedef struct VexNode
{
    ElemType data;
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
Status AddArc(int m, int n, InfoType power, ALGraph *G);
void ShortestPath_DIJ (ALGraph G, int s, int *d);

int main()
{
    int v, s, m, n, power;
    int d[MAX_VERTEX_NUM];
    char c;
    ALGraph G;
    Sqstack M;

    scanf("%d %d", &v, &s);
    getchar();
    CreateGraph(&G);
    AddVertex(v, &G);

    while((c = getchar()) != EOF)
    {
        m = c - '0';
        while ((c = getchar()) != '-')
            m = m * 10 + c - '0';
        scanf("%d %d", &n, &power);
        AddArc(m, n, power, &G);
        getchar();
    }

    ShortestPath_DIJ(G, s, &d[0]);
    for (int i = 1; i <= v; i++)
    {
        if (i != s)
        {
            printf("%d", d[i]);
            if (i != v && (i != v-1 || s != v))
                printf(",");
        }
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
    for (int i = 1; i <= v; i++)
    {
        G->vexnum++;
        G->AdjList[i].data = i;
        G->AdjList[i].firstarc = NULL;
    }
    return OK;
}

Status AddArc(int m, int n, InfoType power, ALGraph *G)
{
    LinkNode *p, *q;
    VexNode *v;
    v = &(G->AdjList[m]);
    q = (LinkNode*)malloc(sizeof(LinkNode));
    q->adjvex = n;
    q->nextarc = NULL;
    q->info = power;
    
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
    return OK;
}

void ShortestPath_DIJ (ALGraph G, int s, int *d)
{
    int final[MAX_VERTEX_NUM];
    LinkNode *p;

    for (int i = 1; i <= G.vexnum; i++)
    {
        final[i] = 0;
        d[i] = INT_MAX;    
    }
    for (p = G.AdjList[s].firstarc; p; p = p->nextarc)
        d[p->adjvex] = p->info;
    d[s] = 0;
    final[s] = 1;

    int v;
    for (int i = 1; i <= G.vexnum; i++)
        if (i != s)
        {
            int min = INT_MAX;
            for (int w = 1; w <= G.vexnum; w++)
                if (final[w] == 0 && d[w] < min)
                {
                    v = w;
                    min = d[w];
                }
            final[v] = 1;
            for (p = G.AdjList[v].firstarc; p; p = p->nextarc)
                if (final[p->adjvex] == 0 && min + p->info < d[p->adjvex])
                    d[p->adjvex] = min + p->info;
        }

}