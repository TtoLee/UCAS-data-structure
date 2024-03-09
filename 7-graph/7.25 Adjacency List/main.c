#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 30
#define ERROR 0
#define OK 1

typedef int ElemType;
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
    LinkNode *firstarc;
} VexNode;
typedef struct ALGraph
{
    GraphKind kind;
    int vexnum, arcnum;
    VexNode AdjList[MAX_VERTEX_NUM];
} ALGraph;

Status CreateGraph(ALGraph *G);
int JudgeInput(int *i, ElemType input[]);
Status AddVertex(int v, ALGraph *G);
Status AddArc(int m, int n, ALGraph *G);
void DFSArticul(ALGraph G, int v, int start, int visited[], int *count, int *flag);

int main()
{
    int s[MAX_VERTEX_NUM], fst[MAX_VERTEX_NUM], lst[MAX_VERTEX_NUM], visited[MAX_VERTEX_NUM];
    int i, v, flag, count;
    char c;
    ALGraph G;

    scanf("%d", &v);
    getchar();
    i = 0;
    do
    {
        scanf("%d", &s[i++]);
    } while ((c = getchar()) != '\n');
    i = 0;
    do
    {
        scanf("%d", &fst[i++]);
    } while ((c = getchar()) != '\n');    
    i = 0;
    do
    {
        scanf("%d", &lst[i++]);
    } while ((c = getchar()) != '\n');    

    AddVertex(v, &G);
    for (int i = 1; i <= v; i++)
        for (int j = fst[i]; j < lst[i]; j++)
            AddArc(i, s[j], &G);
    flag = 0;
    for (int i = 1; i <= v; i++)
    {
        for (int i = 1; i <= v; i++)
            visited[i] = 0;
        count = 0;
        DFSArticul(G, i, i, visited, &count, &flag);
        if (flag == 1)
            break;
    }
    if (flag == 1)
        printf("yes");
    else
        printf("no");
}

Status CreateGraph(ALGraph *G)
{
    G->kind = UDG;
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
        if (p->adjvex < n)
        {
            (*v).firstarc = q;
            q->nextarc = p;
        }
        else
        {
            while (p->nextarc && p->nextarc->adjvex > n)
                p = p->nextarc;
            q->nextarc = p->nextarc;
            p->nextarc = q;
        }
    }
    return OK;
}

void DFSArticul(ALGraph G, int v, int start, int visited[], int *count, int *flag)
{
    visited[v] = ++*count;

    LinkNode *p;
    for (p = G.AdjList[v].firstarc; p; p = (*p).nextarc)
    {
        int w = (*p).adjvex;
        if (visited[w] == 0)
            DFSArticul(G, w, start, visited, count, flag);
        if (w == start)
            *flag = 1;
    }
}