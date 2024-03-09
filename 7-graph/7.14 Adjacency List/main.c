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
int JudgeInput(int a, ElemType *input);
Status AddVertex(int flag, int v, ALGraph *G);
Status AddArc(int a, int flag, ElemType *input, ALGraph *G);
Status OutputGraph(ALGraph G);

int main()
{
    int v, a, flag;
    ElemType *input;
    ALGraph G;
    scanf("%d,%d", &v, &a);
    input = (ElemType*)malloc(2 * a * sizeof(ElemType));
    CreateGraph(&G);
    flag = JudgeInput(a, input);
    AddVertex(flag, v, &G);
    AddArc(a, flag, input, &G);
    OutputGraph(G);
}

Status CreateGraph(ALGraph *G)
{
    G->kind = UDG;
    G->vexnum = 0;
    G->arcnum = 0;
}

int JudgeInput(int a, ElemType *input)
{   
    int flag = 0;
    for (int i = 0; i < a; i++)
    {
        scanf("%d-%d", &input[2 * i], &input[2 * i + 1]);
        if (flag == 0 && input[2 * i] == 0)
            flag = 1;
        getchar();
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

Status AddArc(int a, int flag, ElemType *input, ALGraph *G)
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

Status OutputGraph(ALGraph G)
{
    for (int i = 1; i <= G.vexnum; i++)
    {
        VexNode v = G.AdjList[i];
        printf("%d", v.data);
        if (v.firstarc)
        {
            printf(" ");
            LinkNode *l = v.firstarc;
            while (l)
            {
                printf("%d", G.AdjList[l->adjvex].data);
                if(l->nextarc)
                    printf(",");
                l = l->nextarc;
            }
        }
        if (i != G.vexnum)
            printf("\n");
    }
}