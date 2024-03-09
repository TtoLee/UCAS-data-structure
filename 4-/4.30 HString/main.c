#include <stdio.h>

#define MAXSTRLEN 500

typedef unsigned char Sstring[MAXSTRLEN+1];

void DeleteChar(Sstring S, int n);
int Get_nextval(Sstring T, int maxlen);

int main()
{
    char c;
    Sstring S;
    Sstring T;
    int i, n, maxlen;
    maxlen = 0;
    for (i = 0; (c = getchar()) != '\n'; i++)
        S[i+1] = c;
    S[0] = i;
    S[i+1] = '\0';
    S[i+2] = i;
    for (int j = 0; S[j] != '\0'; j++)
        T[j] = S[j];

    while(maxlen < S[0])
    {
        int t;
        t = Get_nextval(S, maxlen);
        if (t != 0)
            DeleteChar(S, t);
        else
            DeleteChar(S, 1);
        if (t > maxlen)
            maxlen = t;
    }

    if (maxlen == 0)
        printf("-1");
    else
    {
        for (int j = 0; j < maxlen; j++)
            printf("%c", T[i - S[S[0]+2]+1+j]);
        printf(" %d", i - S[S[0]+2]);
    }
}

void DeleteChar(Sstring S, int n)
{
    for (int i = 1; i <= S[0] + 2 - n ; i++)
        S[i] = S[i+n];
    S[0] -= n;
}

int Get_nextval(Sstring T, int maxlen)
{
    int next[MAXSTRLEN + 1];
    int i, j, len;
    next[1] = 0;
    i = 1;
    j = 0;
    len = 0;
    while (i < T[0])
        if (j == 0 || T[i] == T[j])
        {
            i++;
            j++;
            next[i] = j;
            if (j > maxlen && T[i] == T[j])
            {
                T[T[0]+2] = T[0];
                maxlen = j;
                len = j;
            }
        }
        else 
            j = next[j];
    return len;
}