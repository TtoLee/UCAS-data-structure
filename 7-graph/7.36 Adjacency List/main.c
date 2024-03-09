#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 30
#define MAX_ARC_NUM 60
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
Status AddVertex(int flag, int v, ALGraph *G);
Status AddArc(int a, int flag, ElemType input[], ALGraph *G);
void DFSArticul(ALGraph G, int v, int visited[], int count, int *len);

int main()
{
    int v, a, flag, visited[MAX_VERTEX_NUM], count, len;
    ElemType input[MAX_ARC_NUM];
    ALGraph G;
    scanf("%d", &v);
    getchar();
    a = 0;
    CreateGraph(&G);
    flag = JudgeInput(&a, input);
    if (flag != 2)
    {
        AddVertex(flag, v, &G);
        AddArc(a, flag, input, &G);
    }
    else
    {
        flag = 0;
        AddVertex(flag, v, &G);
    }

    for (int i = 1 - flag; i <= G.vexnum - flag; i++)
    {
        for (int i = 0; i < MAX_VERTEX_NUM; i++)
            visited[i] = 0;
        count = 0;
        len = 0;
        DFSArticul(G, i, visited, count, &len);
        printf("%d", len - 1);
        if ( i != G.vexnum - flag)
            printf(",");
    }
}

Status CreateGraph(ALGraph *G)
{
    G->kind = UDG;
    G->vexnum = 0;
    G->arcnum = 0;
    return OK;
}

int JudgeInput(int *i, ElemType input[])
{   
    char c;
    int flag = 0;
    if ((c = getchar()) == '\n')
        return 2;
    input[2 * *i] = c - '0';
    while ((c = getchar()) != '-')
        input[2 * *i] = input[2 * *i] * 10 + c - '0';
    scanf("%d", &input[2 * *i + 1]);
    (*i)++;
    while ((c = getchar()) != '\n')
    {
        scanf("%d-%d", &input[2 * *i], &input[2 * *i + 1]);
        if (flag == 0 && input[2 * *i] == 0)
            flag = 1;
        if (c == '\n')
            break;
        (*i)++;
    }
    return flag;
}

Status AddVertex(int flag, int v, ALGraph *G)
{
    if (v > MAX_VERTEX_NUM) 
        return ERROR;
    for (int i = 1; i <= v; i++)
    {
        G->vexnum++;
        G->AdjList[i].data = i - flag;
        G->AdjList[i].firstarc = NULL;
    }
    return OK;
}

Status AddArc(int a, int flag, ElemType input[], ALGraph *G)
{
    for (int i = 0; i < a; i++)
    {
        LinkNode *p, *q;
        VexNode *v;
        v = &(G->AdjList[input[2 * i] + flag]);
        q = (LinkNode*)malloc(sizeof(LinkNode));
        q->adjvex = input[2 * i + 1] + flag;
        q->nextarc = NULL;
        
        if (!(*v).firstarc)
            (*v).firstarc = q;
        else
        {
            p = (*v).firstarc;
            if (p->adjvex < input[2 * i+1] + flag)
            {
                (*v).firstarc = q;
                q->nextarc = p;
            }
            else
            {
                while (p->nextarc && p->nextarc->adjvex > input[2 * i + 1] + flag)
                    p = p->nextarc;
                q->nextarc = p->nextarc;
                p->nextarc = q;
            }
        }
    }
    return OK;
}

void DFSArticul(ALGraph G, int v, int visited[], int count, int *len)
{
    visited[v] = count++;
    if (count > *len)
        *len = count;
    LinkNode *p;
    for (p = G.AdjList[v].firstarc; p; p = (*p).nextarc)
    {
        int w = (*p).adjvex;
        if (visited[w] == 0)
            DFSArticul(G, w, visited, count, len);
        for (int i = 1; i <= G.vexnum; i++)
            visited[i] = 0;
    }
}