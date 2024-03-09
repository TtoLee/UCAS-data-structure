#include<stdio.h>  
#include<malloc.h> 

#define INITSIZE 100
#define INCREMENTSIZE 10
#define Status int
#define OK 1
#define ERROR 0

typedef char ElemType;
typedef struct 
{
    ElemType *top;
    ElemType *base;
    int stacksize;
} Sqstack;

Status Initstack (Sqstack *s);
Status Push (Sqstack *s, ElemType *e);
Status Pop (Sqstack *s, ElemType *e);

int main()
{
    Sqstack S;
    char c, check;
    char str[1000];
    int len;
    Status state;
    Initstack (&S);
    state = OK;

    for (len = 0; (c = getchar()) != '@'; len++)
    {
        str[len] = c;
        Push(&S, &c);
    }

    for (int i = 0; i < len; i++)
    {
        Pop(&S, &check);
        if (check != str[i])
        {
            printf("0");
            return 0;
        }
    }

    printf("1");
}

Status Initstack (Sqstack *s)
{
    s->base = (ElemType *)malloc(INITSIZE * sizeof(ElemType));
    if (!s)
        return ERROR;
    s->top = s->base;
    s->stacksize = INITSIZE;
    return OK;   
}

Status Push (Sqstack *s, ElemType *e)
{
    if (s->top >= s->base + s->stacksize)
    {
        s->base = (ElemType *)realloc(s->base, (s->stacksize + INCREMENTSIZE) * sizeof(ElemType));
        if (!s->base)
            return ERROR;
        s->stacksize += INCREMENTSIZE;
    }
    *(s->top) = *e;
    s->top++;
    return OK;
}

Status Pop (Sqstack *s, ElemType *e)
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