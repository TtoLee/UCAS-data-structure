#include <stdio.h>
#include <malloc.h>

#define MAX_TREE_SIZE 100
#define ERROR 0
#define OK 1 
#define INITSIZE 100
#define INCREMENTSIZE 10

typedef int Status;
typedef char TElemType;
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *child, *brother;
}BiTNode, *BiTree;

Status CreateBiTree(BiTree *T);
Status CreateNode(BiTree *T, int i, TElemType data[], int lchildren[], int rchildren[]);
Status PrintElement(TElemType e, int n);
Status PreOrderTraverse (BiTree T, Status (* visit)(TElemType e, int n), int n);

int main()
{
    BiTree T;

    CreateBiTree(&T);
    PreOrderTraverse(T, PrintElement, 1);
}

Status CreateBiTree(BiTree *T)
{
    TElemType data[MAX_TREE_SIZE];
    TElemType c;
    int child[MAX_TREE_SIZE], brother[MAX_TREE_SIZE];
    int n = 0;

    while ((c = getchar()) != EOF)
    {
        n++;
        data[n] = c;
        scanf("%d %d", &child[n], &brother[n]);
        getchar();
    }

    CreateNode(T, 1, data, child, brother);
    return OK;
}

Status CreateNode(BiTree *T, int i, TElemType data[], int child[], int brother[])
{
    *T = (BiTree)malloc(sizeof(BiTNode));
    if (!(*T))
        return ERROR;
    (*T)->data = data[i];
    if (child[i] != -1)
    {
        BiTree l;
        CreateNode(&l, child[i], data, child, brother);
        (*T)->child = l;
    }
    else
        (*T)->child = NULL;
    if (brother[i] != -1)
    {
        BiTree r;
        CreateNode(&r, brother[i], data, child, brother);
        (*T)->brother = r;
    }
    else
        (*T)->brother = NULL;
    return OK;
}

Status PrintElement(TElemType e, int n)
{
    for (int i = 1; i < n; i++)
        printf("-");
    printf("%c\n", e);
    return OK;
}

Status PreOrderTraverse (BiTree T, Status (* visit)(TElemType e, int n), int n)
{
    if (T)
    {
        if (visit(T->data, n))
            if (PreOrderTraverse(T->child, visit, n+1))
                if (PreOrderTraverse(T->brother, visit, n))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}