#include <stdio.h>
#include <malloc.h>

#define MAXSTRLEN 100
#define ERROR 0
#define OK 1

typedef unsigned char SString[MAXSTRLEN+1];
typedef int Status;
typedef char AtomType;
typedef enum {ATOM, LIST} ElemTag;
typedef struct GLNode
{
    ElemTag tag;
    union
    {
        AtomType atom;
        struct {
            struct GLNode *hp, *tp;
        }ptr;
    };
}GLNode, *GList;

Status CreateList (GList *L, SString S);                        //创建一个以S为输入的广义表
Status serve (SString str, SString hstr);                       //将str以第一个出现的逗号分成两部分, 前一部分赋给hstr, 后一部分给str
Status PrintList (GList s);                                     //打印广义表
void DeleteListData (GList *s, AtomType c);                     //删除广义表中所有值等于c的项
Status DeleteList (GList *S);                                   //删除子表
void DeleteEmptyList(GList *S);                                 //删除空表
int GlistDepth (GList L);                                       //求广义表的深度
Status InitSString (SString S);                                 //初始化顺序存储字符串
int StrComp (SString S, SString T);                             //判断两个字符串是否相等
Status SubString (SString Sub, SString S, int pos, int len);    //从S第pos个位置开始, 取len长的字符串, 赋给Sub
void StrCopy (SString hstr, SString str);                       //把字符串str复制给hstr
void ClearString (SString str);                                 //清除字符串

int main()
{
    SString S;
    GList L;
    char del;

    InitSString (S);
    CreateList (&L, S);
    int n = GlistDepth(L);

    scanf("%c", &del);
    DeleteListData (&L, del);
    for (int i = 0; i < n; i++)
        DeleteEmptyList(&L);
    PrintList (L);
}

Status CreateList (GList *L, SString S)
{
    SString emp, sub, hsub;
    emp[0] = 2;
    emp[1] = '(';
    emp[2] = ')';

    if (StrComp (S, emp))
        *L = NULL;
    else
    {
        *L = (GList) malloc (sizeof (GLNode));
        if (!L)
            return ERROR;
        if (S[0] == 1)
        {
            (*L)->tag = ATOM;
            (*L)->atom = S[1];
        }
        else
        {
            GList p, q;
            (*L)->tag = LIST;
            p = *L;
            SubString(sub, S, 2, S[0] - 2);
            do {
                serve(sub, hsub);
                CreateList(&p->ptr.hp, hsub);
                q = p;
                if (sub[0] != 0)
                {
                    if (!(p = (GList) malloc (sizeof(GLNode))))
                        return ERROR;
                    p->tag = LIST;
                    q->ptr.tp = p;
                }
            }while (sub[0] != 0);
            q->ptr.tp = NULL;
        }
    }
    return OK;
}

Status serve (SString str, SString hstr)
{
    int n, i, k;
    SString ch;
    n = str[0];
    i = 0;
    k = 0;
    do {
        i++;
        SubString(ch, str, i, 1);
        if (ch[1] == '(')
            k++;
        else if (ch[1] == ')')
            k--;
    }while (i < n && (ch[1] != ',' || k != 0));
    if (i < n)
    {
        SubString (hstr, str, 1, i - 1);
        SubString (str, str, i + 1, n - i);
    }
    else
    {
        StrCopy (hstr, str);
        ClearString (str);
    }
}

Status PrintListData (GList s);
Status PrintList (GList s)
{
    if (!s)
    {
        printf("-1");
        return OK;
    }
    printf("(");
    PrintListData(s);
    printf(")");
}

Status PrintListData (GList s)
{
    if (s->tag == LIST)
    {
        if (!s->ptr.hp);
        else if (s->ptr.hp->tag == LIST)
        {
            printf("(");
            PrintListData(s->ptr.hp);
            printf(")");
        }
        else
            PrintListData(s->ptr.hp);
    }
    else if (s->tag == ATOM)
        printf("%c", s->atom);
    if(s->ptr.tp && s->tag == LIST)
    {
        printf(",");
        PrintListData(s->ptr.tp);
    }
    return OK;
}

void DeleteListData (GList *S, AtomType c)
{
    GList p, q;

    if (*S && (*S)->tag == LIST)
    {
        p = (*S)->ptr.hp;
        if (p)
        {
            if (p->tag == LIST)
            {
                DeleteListData(&((*S)->ptr.hp), c);
                DeleteListData(&((*S)->ptr.tp), c);
            }
            else if (p->tag == ATOM)
            {
                if (p->atom == c)
                {
                    q = *S;
                    *S = (*S)->ptr.tp;
                    q->ptr.tp = NULL;
                    DeleteList(&q);
                    DeleteListData(S, c);
                }
                else
                    DeleteListData(&(*S)->ptr.tp, c);
            }
        }
        else
            if ((*S)->ptr.tp)
                DeleteListData(&(*S)->ptr.tp, c);
    }
}

Status DeleteList(GList *S)
{
    GList head, tail;

    if (!S || !(*S))
        return ERROR;
    if ((*S)->tag == ATOM)
    {
        free(*S);
        *S = NULL;
    }
    else
    {
        head = (*S)->ptr.hp;
        free(*S);
        *S = NULL;
        DeleteList(&head);
    }

    return OK;
}

void DeleteEmptyList(GList *S)
{
    GList p;
    if (*S && (*S)->tag != ATOM)
    {
        if (!(*S)->ptr.hp)
        {
            p = *S;
            *S = (*S)->ptr.tp;
            DeleteList(&p);
            DeleteEmptyList(S);
        }
        else
        {
            DeleteEmptyList(&(*S)->ptr.hp);
            DeleteEmptyList(&(*S)->ptr.tp);
        }
    }
}

int GlistDepth (GList L)
{
    static int max;
    int dep;
    GList pp;

    if (!L)
        return 1;
    if (L->tag == ATOM)
        return 0;
    for (max = 0, pp = L; pp; pp = pp->ptr.tp)
    {
        dep = GlistDepth(pp->ptr.hp);
        if (dep > max)
            max = dep;
    }
    return max+1;
}

Status InitSString (SString S)
{
    char c;
    int i;
    for (i = 1; (c = getchar()) != ' '; i++)
        S[i] = c;
    S[0] = i - 1;
}

int StrComp (SString S, SString T)
{
    if (S[0] != T[0])
        return 0;
    else
        for (int i = 1; i <= S[0]; i++)
            if (S[i] != T[i])
                return 0;
    return 1;
}

Status SubString (SString Sub, SString S, int pos, int len)
{
    if (pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
        return ERROR;
    for (int i = 1; i <= len; i++)
        Sub[i] = S[pos + i - 1];
    Sub[0] = len;
    return OK;
}

void StrCopy (SString hstr, SString str)
{
    for (int i = 0; i <= str[0]; i++)
        hstr[i] = str[i];
}

void ClearString (SString str)
{
    str[0] = 0;
}