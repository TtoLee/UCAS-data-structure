#include <stdio.h>
#include <malloc.h>

#define INITSTRLEN 100
#define ERROR 0
#define MaxSize 500
#define OK 1

typedef int Status;
typedef struct 
{
    char *ch;
    int length;
    int strsize;
} Hstring;

Status StrInit (Hstring *s);
Status StrAssign (Hstring *s, char *sc);
Status StrReplace (Hstring *S, Hstring T, Hstring R);

int main()
{
    Hstring S, T, R, h;
    int i;
    char c[MaxSize];
    char read;
    StrInit(&S);
    StrInit(&T);
    StrInit(&R);

    for (i = 0; (read = getchar()) != ' '; i++)
        c[i] = read;
    c[i] = '\0';
    StrAssign (&S, &c[0]);
    
    for (i = 0; (read = getchar()) != ' '; i++)
        c[i] = read;
    c[i] = '\0';
    StrAssign (&T, &c[0]);

    for (i = 0; (read = getchar()) != '\n'; i++)
    c[i] = read;
    c[i] = '\0';
    StrAssign (&R, &c[0]);

    StrReplace (&S, T, R);

    h = S;
    for (int i = 0; h.ch[i] != '\0'; i++)
        printf("%c", h.ch[i]);

}

Status StrInit (Hstring *s)
{
    s->ch = (char *)malloc(INITSTRLEN * sizeof(char));
    if (!s->ch)
        return ERROR;
    s->ch[0] = '\0';
    s->length = 0;
    s->strsize = INITSTRLEN;
    return OK;
}

Status StrAssign (Hstring *s, char *sc)
{
    int i = 0;
    while (sc[i] != '\0')
        i++;
    if (i >= s->strsize)
    {
        s->ch = (char *)realloc(s->ch, (i+1)*sizeof(char));
        if (!s->ch)
            return ERROR;
        s->strsize = i+1;
    }
    s->length = i;
    for (i = 0; i < s->length; i++)
        s->ch[i] = sc[i];
    s->ch[i] = '\0';
    return OK;
}

Status StrReplace (Hstring *S, Hstring T, Hstring R)
{
    int flag, begin, k;
    flag = 0;

    for (int i = 0; i <= S->length - T.length; i++)
    {
        for (int j = 0; j < T.length; j++)
        {
            if (S->ch[i + j] != T.ch[j])
                break;
            if (j == T.length - 1)
            {
                flag = 1;
                begin = i + 1;
                break;
            }
        }
        if (flag == 1)
            break;
    }

    if (!flag)
        return ERROR;
    
    if (T.length < R.length)
    {
        if (S->length + R.length - T.length)
        {
            S->ch = (char *)realloc(S->ch, (S->length + R.length - T.length)*sizeof(char));
            if (!S->ch)
                return ERROR;
            S->strsize = S->length + R.length - T.length;
        }
        for (k = S->length; k >= begin + T.length -1; k--)
            S->ch[k - T.length + R.length] = S->ch[k];
    }
    else
        for (k = begin + T.length - 1; k < S->length; k++)
            S->ch[k - T.length + R.length] = S->ch[k];
    
    S->length = S->length + R.length - T.length;
    S->ch[S->length] = '\0';
    for (k = 0; k < R.length; k++)
        S->ch[k + begin - 1] = R.ch[k];
    return OK;
}