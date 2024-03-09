#include <stdio.h>
#include <malloc.h>

#define ERROR 0
#define OK 1

typedef int Status;
typedef int ElemType;
typedef struct OLNode
{
    int i, j;
    ElemType e;
    struct OLNode *right, *down;
} OLNode, *OLink;

typedef struct 
{
    OLink *rhead, *chead;
    int mu, nu, tu;
} CrossList;

Status InitSMatrix_OL (CrossList *M, int m, int n);
Status CreateSMatrix_OL (CrossList *M, int i, int j, ElemType e);
Status InputSMatrix (CrossList *A);
Status AddSMatrix(CrossList *A, CrossList *B);

int main()
{
    CrossList A, B;
    int m, n;
    scanf("%d %d", &m, &n);

    InitSMatrix_OL (&A, m, n);
    InitSMatrix_OL (&B, m, n);

    InputSMatrix (&A);
    InputSMatrix (&B);

    AddSMatrix (&A, &B);

    int number = 0;
    for (int i = 1; i <= A.mu; i++)
    {
        OLink p = A.rhead[i];
        while (p)
        {
            if (!number)
                printf ("%d", p->e);
            else
                printf(" %d", p->e);
            p = p->right;
            number++;
        }
    }
    printf("\n");

    for (int i = 1; i <= A.mu; i++)
    {
        int num;
        OLink p = A.rhead[i];
        for (int j = 1; j <= A.nu; j++)
        {
            if (!p || j != p->j)
                num = 0;
            else
            {
                num = 1;
                p = p->right;
            }
            if (j == 1)
                printf("%d", num);
            else
                printf(" %d", num);
        }
        if (i != A.mu)
            printf("\n");
    }
}

Status InitSMatrix_OL (CrossList *M, int m, int n)
{
    M->mu = m;
    M->nu = n;
    M->tu = 0;
    M->rhead = (OLink *)malloc((m+1) * sizeof(OLink));
    M->chead = (OLink *)malloc((n+1) * sizeof(OLink));
    if (!M->chead || !M->chead)
        return ERROR;
    for (int i = 0; i <= m; i++)
        M->rhead[i] = NULL;
    for (int i = 0; i <= n; i++)
        M->chead[i] = NULL;
}

Status CreateSMatrix_OL (CrossList *M, int i, int j, ElemType e)
{
    OLink p, q;
    p = (OLink)malloc(sizeof(OLNode));
    if (!p)
        return ERROR;
    p->i = i;
    p->j = j;
    p->e = e;
    if (M->rhead[i] == NULL || M->rhead[i]->j > j)
    {
        p->right = M->rhead[i];
        M->rhead[i] = p;
    }
    else
    {
        for (q = M->rhead[i]; (q->right) && q->right->j < j; q = q->right);
        p->right = q->right;
        q->right = p;
    }

    if (M->chead[j] == NULL || M->chead[j]->i > i)
    {
        p->down = M->chead[j];
        M->chead[j] = p;
    }
    else
    {
        for (q = M->chead[j]; (q->down) && q->down->i < i; q = q->down);
        p->down = q->down;
        q->down = p;
    }

    M->tu++;
    return OK;
}

Status InputSMatrix (CrossList *A)
{
    ElemType data;
    ElemType *a_data;
    int len, cur;
    char c;
    len = 0;

    scanf("%d", &data);
    if (data == 0)
        for (int i = 0; i < A->mu; i++)
            for (int j = 0; j < A->nu; j++)
            {
                if (i || j)
                    scanf("%d", &data);
            }
    else
    {
        a_data = (ElemType *)malloc(sizeof(ElemType));
        a_data[0] = data;
        len++;
        while ((c = getchar()) != '\n')
        {
            scanf("%d", &data);
            a_data = (ElemType *)realloc(a_data, (len + 1) * sizeof(ElemType));
            a_data[len] = data;
            len++;
        }
        cur = 0;
        for (int i = 1; i <= A->mu; i++)
            for (int j = 1; j <= A->nu; j++)
            {
                scanf("%d", &data);
                if (data)
                {
                    CreateSMatrix_OL (A, i, j, a_data[cur]);
                    cur++;
                }
            }
    }
}

Status AddSMatrix(CrossList *A, CrossList *B)
{
    OLink pa, pb, pre;
    OLink *hl;

    hl = (OLink *)malloc((A->nu + 1) * sizeof(OLink));
    for (int j = 1; j <= A->nu; j++)
        hl[j] = A->chead[j];
    
    for (int i = 1; i <= A->mu; i++)
    {
        pre = NULL;
        pa = A->rhead[i];
        pb = B->rhead[i];

        while (pb != NULL)
        {
            if (pa == NULL || pa->j > pb->j)
            {
                OLink p = (OLink)malloc(sizeof(OLNode));
                p->e = pb->e;
                p->i = pb->i;
                p->j = pb->j;
                if (pre == NULL)
                    A->rhead[p->i] = p;
                else 
                    pre->right = p;
                p->right = pa;
                pre = p;
                if (!A->chead[p->j] || A->chead[p->j]->i > p->i)
                {
                    p->down = A->chead[p->j];
                    A->chead[p->j] = p;
                }
                else
                {
                    p->down = hl[p->j]->down;
                    hl[p->j]->down = p;
                }
                hl[p->j] = p;
                pb = pb->right;
            }
            else if (pa != NULL && pa->j < pb->j)
            {
                pre = pa;
                pa = pa->right;
            }
            else if (pa->j == pb->j)
            {
                pa->e += pb->e;
                if (pa->e == 0)
                {
                    if (pre == NULL)
                        A->rhead[pa->i] = pa->right;
                    else
                        pre->right = pa->right;
                    OLink p = (OLink)malloc(sizeof(OLNode));
                    p->e = pa->e;
                    p->i = pa->i;
                    p->j = pa->j;
                    pa = pa->right;
                    if (A->chead[p->j] == p)
                    {
                        hl[p->j] = p->down;
                        A->chead[p->j] = hl[p->j];
                    }
                    else
                        hl[p->j]->down = p->down;
                    free(p);
                }
                pb = pb->right;
            }
        }
    }
}