#include <stdio.h>
#include <malloc.h>

#define INITSTRLEN 100
#define ERROR 0
#define OK 1
#define MaxSize 500

typedef int Status;
typedef struct 
{
    char *ch;
    int length;
    int strsize;
} Hstring;

Status StrInit (Hstring *s);
Status StrAssign (Hstring *s, char *sc);
int StrLen (Hstring *s);
int StrComp (Hstring *s, Hstring *t);

int main()
{
    Hstring S, T, h;
    int i, sign;
    char c[MaxSize];
    char read;
    StrInit(&S);
    StrInit(&T);

    for (i = 0; (read = getchar()) != ' '; i++)
        c[i] = read;
    c[i] = '\0';
    StrAssign (&S, &c[0]);
    
    for (i = 0; (read = getchar()) != '\n'; i++)
        c[i] = read;
    c[i] = '\0';
    StrAssign (&T, &c[0]);

    sign = StrComp(&S, &T);
    printf("%d", sign);
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

int StrLen (Hstring *s)
{
    return s->length;
}

int StrComp (Hstring *s, Hstring *t)
{
    for (int i = 0; i < s->length && i < s->length; i++)
        if (s->ch[i] != t->ch[i])
        {
            if (s->ch[i] > t->ch[i])
                return 1;
            else
                return -1;
        }
    return 0;
}