#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

#define CONTINUE 1
#define BREAK 0

typedef struct node
{
    int coef;
    int expn;
    struct node *next;
}Polynomial, *Polycur;

void InitPoly (Polycur *P);                     //初始化多项式列表
void CreatePoly (Polycur *P, int co, int exp);  //将系数为co, 指数为exp的式子插入多项式
int GetNum(Polycur *P);                         //读取输入
void Reverse(Polycur *P);                       //将多项式由降(升)序排列变为升(降)序排列
void Derivative(Polycur *P);                    //对输入的降序多项式求导

int main()
{
    Polycur P, h;
    InitPoly (&P);
    int state = CONTINUE;

    while (state == CONTINUE)
        state = GetNum(&P);

    Derivative (&P);

    h = P->next;
    if (h == P)
        printf("0");
    else
        for (int i = 0; h != P; i++)
        {
            int c = h->coef;
            if (i == 0)
            {
                if (h->coef < 0)
                {
                    printf("- ");
                    c = -c;
                }

                if (h->expn == 0)
                    printf("%d", c);
                else if (h->expn == 1)
                    printf("%dx", c);
                else if (h->expn > 1)
                    printf("%dx^%d", c, h->expn);
            }
            else
            {
                if (h->coef > 0)
                    printf (" + ");
                else if (h->coef < 0)
                {
                    printf(" - ");
                    c = -c;
                }
                
                if (h->expn == 0)
                    printf("%d", c);
                else if (h->expn == 1)
                    printf("%dx", c);
                else if (h->expn > 1)
                    printf("%dx^%d", c, h->expn);
            }
            h = h->next;
        }
}

int GetNum(Polycur *P)
{
    int coe, exp, type;
    char c;
    c = getchar();

    if (c == '-')
    {
        type = -1;
        getchar();
        c = getchar();
        if (c == 'x')
            coe = 1;
        else if (isdigit(c))
            coe = c - '0';
    }
    else if (c == '+')
    {
        type = 1;
        coe = 0;
        getchar();
        c = getchar();
        if (c == 'x')
            coe = 1;
        else if (isdigit(c))
            coe = c - '0';
    }

    else if (c == 'x')
    {
        type = 1;
        coe = 1;
    }
    else if (isdigit(c))
    {
        type = 1;
        coe = c - '0';
    }
    
    if (c != 'x')
        while (isdigit(c = getchar()))
            coe = coe * 10 + c - '0';
    coe *= type;
    if (c == 'x')
    {
        c = getchar();
        if (c == '^')
        {
            scanf("%d", &exp);
            c = getchar();
        }
        else if (c == ' ' || c == '\n')
            exp = 1;
    }    
    else if (c == ' ' || c == '\n')
        exp = 0;
    
    CreatePoly (P, coe, exp);
    if (c == '\n')
        return BREAK;
    else
        return CONTINUE;
}

void InitPoly (Polycur *P)
{
    Polycur q;

    *P = (Polycur)malloc(sizeof(Polynomial));
    q = (Polycur)malloc(sizeof(Polynomial));
    (*P)->next = q;
    q->next = *P;
    (*P)->expn = 0;
    q->expn = 0;
    q->coef = 0;
}

void CreatePoly (Polycur *P, int co, int exp)
{
    if (exp <= (*P)->expn)
    {
        Polycur r;
        r = (*P)->next;
        for (int i = 1; i <= (*P)->expn - exp; i++)
            r = r->next;
        r->coef += co;
    }
    else
    {
        for (int i = 1; i <= exp - (*P)->expn;)
        {
            Polycur q, r;
            r = (*P)->next;
            q = (Polynomial*)malloc(sizeof(Polynomial));
            q->next = r;
            q->expn = (*P)->expn + 1;
            q->coef = 0;
            (*P)->next = q;
            (*P)->expn++;
        }
        (*P)->next->coef = co;
    }
}

void Reverse(Polycur *P)
{
    Polycur l, m, n;
    l = (*P)->next;
    n = *P; 
    while (l != *P)
    {
        m = l;
        l = l->next;
        m->next = n;
        n = m;
    }
    (*P)->next = m;
}

void Derivative(Polycur *P)
{
    Polycur h;
    Reverse(P);
    h = (*P)->next;

    for (int i = 0; i < (*P)->expn; i++)
    {
        h->coef = h->next->coef * h->next->expn;
        h = h->next;
    }
    h->coef = 0;
    
    Reverse(P);
    h = (*P);
    for (int i = 0; i <= (*P)->expn; i++)
    {
        Polycur r = h->next;
        if (r->coef == 0)
        {
            h->next = r->next;
            free(r);
        }
        else
            h = h->next;
    }
}