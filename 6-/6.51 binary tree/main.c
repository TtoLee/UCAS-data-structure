#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100
#define ERROR 0
#define OK 1 

typedef int Status;
typedef char TElemType;
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

Status CreateBiTree(BiTree *T);                                 //与下面一个函数一起创造树
Status CreateNode(BiTree *T, int *i, int n, TElemType data[]);
Status AddBracket (BiTree *T);                                  //增加括号
Status PostOrderTraverse (BiTree T, Status (* visit)(BiTree *L));//后序遍历
Status PrintElement(TElemType e);                               //打印树
Status InOrderTraverse (BiTree T, Status (* visit)(TElemType e));//中序遍历

int main()
{
    BiTree T;

    CreateBiTree(&T);
    PostOrderTraverse(T, AddBracket);
    InOrderTraverse(T, PrintElement);
    return 0;
}

Status CreateBiTree(BiTree *T)
{
    TElemType c, data[2 * MAX_TREE_SIZE + 3];
    int n;
    n = 0;

    while ((c=getchar()) != '\n')
        data[++n] = c;

    int i = 1;
    CreateNode(T, &i, n, data);
    return OK;
}

Status CreateNode(BiTree *T, int *i, int n, TElemType data[])
{
    *T = (BiTree)malloc(sizeof(BiTNode));
    if (!(*T))
        return ERROR;
    (*T)->data = data[*i];

    if (*i != n)
    {
        if (data[++(*i)] != '#')
        {
            BiTree L;
            CreateNode(&L, i, n, data);
            (*T)->lchild = L;
        }
        else
            (*T)->lchild = NULL;
    }
    if (*i != n)
    {
        if (data[++(*i)] != '#')
        {
            BiTree L;
            CreateNode(&L, i, n, data);
            (*T)->rchild = L;
        }
        else
            (*T)->rchild = NULL;
    }
    return OK;
}

Status AddBracket (BiTree *T)//如果一个节点数据时+或-,且右子树也是+或-,需要加括号. 节点数据是*或/, 左子树是+或-, 右子树是*或/市也需要加括号
{
    if (*T)
    {
        if ((*T)->data == '+' || (*T)->data == '-' || (*T)->data == '*' || (*T)->data == '/')
        {
            BiTree p;
            if ((*T)->data == '+' || (*T)->data == '-')
            {
                if ((*T)->rchild->data == '+' || (*T)->rchild->data == '-')
                {
                    p = (*T)->rchild;
                    while (p->lchild)
                        p = p->lchild;
                    BiTree l = (BiTree)malloc(sizeof(BiTNode));
                    l->data = '(';
                    l->lchild = NULL;
                    l->rchild = NULL;
                    p->lchild = l;
                    p = (*T)->rchild;
                    while (p->rchild)
                        p = p->rchild;
                    BiTree r = (BiTree)malloc(sizeof(BiTNode));
                    r->data = ')';
                    r->lchild = NULL;
                    r->rchild = NULL;
                    p->rchild = r;
                }
            }
            else if ((*T)->data == '*' || (*T)->data == '/')
            {
                if ((*T)->lchild->data == '+' || (*T)->lchild->data == '-')
                {
                    p = (*T)->lchild;
                    while (p->lchild)
                        p = p->lchild;
                    BiTree l = (BiTree)malloc(sizeof(BiTNode));
                    l->data = '(';
                    l->lchild = NULL;
                    l->rchild = NULL;
                    p->lchild = l;
                    p = (*T)->lchild;
                    while (p->rchild)
                        p = p->rchild;
                    BiTree r = (BiTree)malloc(sizeof(BiTNode));
                    r->data = ')';
                    r->lchild = NULL;
                    r->rchild = NULL;
                    p->rchild = r;
                }
                if ((*T)->rchild->data == '*' || (*T)->rchild->data == '/')
                {
                    p = (*T)->rchild;
                    while (p->lchild)
                        p = p->lchild;
                    BiTree l = (BiTree)malloc(sizeof(BiTNode));
                    l->data = '(';
                    l->lchild = NULL;
                    l->rchild = NULL;
                    p->lchild = l;
                    p = (*T)->rchild;
                    while (p->rchild)
                        p = p->rchild;
                    BiTree r = (BiTree)malloc(sizeof(BiTNode));
                    r->data = ')';
                    r->lchild = NULL;
                    r->rchild = NULL;
                    p->rchild = r;
                }
            }
        }
    }
    return OK;
}

Status PostOrderTraverse (BiTree T, Status (* visit)(BiTree *L))
{
    if (T)
    {
        if (PostOrderTraverse(T->lchild, visit))
            if (PostOrderTraverse(T->rchild, visit))
                if (visit(&T))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

Status PrintElement(TElemType e)
{
    printf("%c", e);
    return OK;
}

Status InOrderTraverse (BiTree T, Status (* visit)(TElemType e))
{
    if (T)
    {
        if (InOrderTraverse(T->lchild, visit))
            if (visit(T->data))
                if (InOrderTraverse(T->rchild, visit))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}