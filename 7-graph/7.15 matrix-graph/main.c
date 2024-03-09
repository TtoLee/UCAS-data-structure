#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 30
#define ERROR 0
#define OK 1

typedef int ElemType;
typedef int InfoType;
typedef int Status;
typedef enum {DG, UDG, DN, UDN} GraphKind;
typedef struct ArcCell
{
    int adj;
    InfoType *info;
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct 
{
    GraphKind kind;
    int vexnum, arcnum;
    AdjMatrix arcs;
}MGraph;

Status InitMatrix(MGraph *G);
Status InputMatrix(MGraph *G);
Status Operate(MGraph *G);
Status InsertArc(MGraph *G, int i, int j);
Status DeleteArc(MGraph *G, int i, int j);
Status InsertVex(MGraph *G, int m);
Status DeleteVex(MGraph *G, int m);
Status OutputGraph(MGraph G);

int main()
{
    MGraph G;
    char c;

    InitMatrix(&G);
    InputMatrix(&G);
    while(Operate(&G));
    OutputGraph(G);
}

Status InitMatrix(MGraph *G)
{
    (*G).vexnum = 0;
    (*G).arcnum = 0;
    (*G).kind = UDG;
    for (int i = 0; i < MAX_VERTEX_NUM; i++)
        for (int j = 0; j < MAX_VERTEX_NUM; j++)
            (*G).arcs[i][j].adj = 0;
    return OK;
}

Status InputMatrix(MGraph *G)
{
    int vnum;
    scanf("%d", &vnum);
    getchar();
    (*G).vexnum = vnum;
    for (int i = 0; i < vnum; i++)
    {
        for (int j = 0; j < vnum; j++)
        {
            scanf("%d", &(*G).arcs[i][j].adj);
            if (i > j && (*G).arcs[i][j].adj== 1)
                (*G).arcnum++;
        }
        getchar();
    }
    return OK;
}

Status Operate(MGraph *G)
{
    char c, op[3];
    op[0] = getchar();
    if (op[0] == EOF)
        return ERROR;
    int a, b;
    scanf("%c", &op[1]);
    if (op[1] == 'A')
    {
        scanf("%d %d", &a, &b);
        if (op[0] == 'D')
            DeleteArc(G, a, b);
        else
            InsertArc(G, a, b);
    }
    else if (op[1] == 'V')
    {
        scanf("%d", &a);
        if (op[0] == 'D')
            DeleteVex(G, a);
        else
            InsertVex(G, a);
    }
    getchar();
    return OK;
}

Status InsertArc(MGraph *G, int i, int j)
{
    (*G).arcs[i][j].adj = 1;
    (*G).arcs[j][i].adj = 1;
    (*G).arcnum++;
    return OK;
}

Status DeleteArc(MGraph *G, int i, int j)
{
    (*G).arcs[i][j].adj = 0;
    (*G).arcs[j][i].adj = 0;
    (*G).arcnum--;
    return OK;
}

Status InsertVex(MGraph *G, int m)
{
    (*G).vexnum++;
    for (int i = (*G).vexnum; i > m; i--)
        for (int j = (*G).vexnum - 1; j > m; j--)
            (*G).arcs[i][j].adj = (*G).arcs[i - 1][j - 1].adj;
    for (int i = 0; i <= (*G).vexnum; i++)
    {
        (*G).arcs[m][i].adj = 0;
        (*G).arcs[i][m].adj = 0;
    }
    return OK;
}

Status DeleteVex(MGraph *G, int m)
{
    (*G).vexnum--;
    for (int i = m; i < (*G).vexnum; i++)
        for (int j = m; j < (*G).vexnum; j++)
            (*G).arcs[i][j].adj = (*G).arcs[i + 1][j + 1].adj;
    return OK;
}

Status OutputGraph(MGraph G)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            printf("%d", G.arcs[i][j].adj);
            if (j != G.vexnum - 1)
                printf(" ");
        }
        if (i != G.vexnum - 1)
            printf("\n");
    }
}