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
    Status state;
    Initstack (&S);
    state = OK;

    while ((c = getchar()) != '\n')
    {
        if (c == '(')
            Push (&S, &c);
        else if (c == ')')
            state = Pop (&S, &check);
        if (state == ERROR)
        {
            printf("0");
            return 0;
        }
    }

    if (Pop (&S, &check))
        printf("0");
    else
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