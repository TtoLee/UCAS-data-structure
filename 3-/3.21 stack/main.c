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
Status GetTop (Sqstack *s, ElemType *e);
Status Empty (Sqstack s);

int main()
{
    Sqstack S;
    char c, check, ope, top;
    Status state;
    Initstack (&S);

    while((c = getchar()) != '\n')
    {
        if (c == '(')
            Push (&S, &c);
        else if (c == '*' || c == '/')
        {
            if (GetTop(&S, &top))
                if (top == '*' || top == '/')
                {
                    Pop (&S, &ope);
                    printf("%c", ope);
                }
            Push (&S, &c);
        }
        else if (c == '+' || c == '-')
        {
            if (GetTop(&S, &top))
                if (top == '*' || top == '/')
                    while (!Empty(S))
                {
                    Pop (&S, &ope);
                    if (ope == '(')
                    {
                        Push (&S, &ope);
                        break;
                    }
                    else
                        printf("%c", ope);
                }
                else if (top == '+' || top == '-')
                {
                    Pop (&S, &ope);
                    printf("%c", ope);
                }
            Push (&S, &c);
        }
        else if (c == ')')
        {
            Pop (&S, &ope);
            while (ope != '(')
            {
                printf ("%c", ope);
                Pop (&S, &ope);
            }
        }
        else
            printf("%c", c);
    }

    while (!Empty(S))
    {
        Pop(&S, &ope);
        printf("%c", ope);
    }
    
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

Status Empty (Sqstack s)
{
    if (s.top == s.base)
        return 1;
    else 
        return 0;
}

Status GetTop (Sqstack *s, ElemType *e)
{
    if (s->top == s->base)
        return ERROR;
    *e = *(s->top - 1);
    return OK;
}