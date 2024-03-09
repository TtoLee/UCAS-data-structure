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
int StrLen (Hstring *s);
Status StrReverse (Hstring *s);

int main()
{
    Hstring S, h;
    int i;
    char c[MaxSize];
    char read;
    StrInit(&S);

    for (i = 0; (read = getchar()) != '\n'; i++)
        c[i] = read;
    c[i] = '\0';
    StrAssign (&S, &c[0]);
    StrReverse (&S);
    
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

int StrLen (Hstring *s)
{
    return s->length;
}

Status StrReverse (Hstring *s)
{
    char tem;
    static int i = 0;
    int len = StrLen(s);
    while (i < len/2)
    {
        tem = s->ch[i];
        s->ch[i] = s->ch[len-i-1];
        s->ch[len-i-1] = tem;
        i++;
    }
}