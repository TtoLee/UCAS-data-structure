#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define MAXKEYLEN 16
#define AlphabetLen 27

typedef int Status;
typedef struct KeysType
{
    char ch[MAXKEYLEN];
    int len;
} KeysType;

typedef struct TrieNode 
{
    int leaf;

    struct {KeysType K;}lf;
    struct {struct TrieNode *ptr[AlphabetLen]; int num;} bh;
}TrieNode, *TrieTree;


Status InitTree(TrieTree *T);
Status AddNode (TrieTree *T, char *data);
Status DelNode (TrieTree *T, char *data);
Status SearchNode (TrieTree *T, char *data);
Status Operation (TrieTree *T);

int main()
{
    TrieTree T;
    T = (TrieTree)malloc(sizeof(TrieNode));
    InitTree(&T);
    Operation (&T);
}

Status Operation (TrieTree *T)
{
    char c, data[MAXKEYLEN];
    int state;
    while ((c = getchar()) != EOF)
    {
        scanf("%s", &data);
        switch (c)
        {
        case '1':
            AddNode(T, &data[0]);
            break;
        case '2':
            DelNode(T, &data[0]);
            break;
        case '3':
            state = SearchNode(T, &data[0]);
            if (state)
                printf("True\n");
            else
                printf("False\n");
        break;
        default:
            break;
        }
        getchar();
    }
}

Status InitTree(TrieTree *T)
{    
    (*T)->leaf = 0;
    for (int i = 0; i < AlphabetLen; i++)
        (*T)->bh.ptr[i] = NULL;
    (*T)->bh.num = 0;
}

Status AddNode (TrieTree *T, char *data)
{
    if (strlen(data) > MAXKEYLEN)
        return ERROR;
    
    TrieTree p, temp;

    if (!T)
        return ERROR;
    p = *T;
    for (int i = 0; data[i] != '\0'; i++)
    {
        if (!p->bh.ptr[data[i] - 'a' + 1])
        {
            temp =  (TrieTree)malloc(sizeof(TrieNode));
            InitTree(&temp);
            p->bh.ptr[data[i] - 'a' + 1] = temp;
        }
        p = p->bh.ptr[data[i] - 'a' + 1];
    }
    temp =  (TrieTree)malloc(sizeof(TrieNode));
    InitTree(&temp);
    p->bh.ptr[0] = temp;
    p = p->bh.ptr[0];
    p->leaf = 1;
    *p->lf.K.ch = *data;
}

Status DelNode (TrieTree *T, char *data)
{
    if (strlen(data) > MAXKEYLEN)
        return ERROR;
    
    TrieTree p, temp;

    if (!T)
        return ERROR;
    p = *T;
    for (int i = 0; data[i] != '\0'; i++)
    {
        if (!p->bh.ptr[data[i] - 'a' + 1])
            return ERROR;
        p = p->bh.ptr[data[i] - 'a' + 1];
    }
    if (p->bh.ptr[0] != NULL && p->bh.ptr[0]->leaf == 1)
    {
        free(p->bh.ptr[0]);
        p->bh.ptr[0] = NULL;
        return OK;
    }
    else
        return ERROR;
}

Status SearchNode (TrieTree *T, char *data)
{
    if (strlen(data) > MAXKEYLEN)
        return ERROR;
    
    TrieTree p, temp;

    if (!T)
        return ERROR;
    p = *T;
    for (int i = 0; data[i] != '\0'; i++)
    {
        if (!p->bh.ptr[data[i] - 'a' + 1])
            return ERROR;
        p = p->bh.ptr[data[i] - 'a' + 1];
    }
    if (p->bh.ptr[0] != NULL && p->bh.ptr[0]->leaf == 1)
        return OK;
    else
        return ERROR;
}