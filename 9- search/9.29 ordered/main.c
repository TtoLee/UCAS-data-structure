#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef int Status;
typedef int KeyType;
typedef struct SElemType
{
    KeyType key;
    struct SElemType *next_key; 
} SElement;
typedef struct SSTable
{
    SElement *begin;
    int length;
} SSTable;

Status InitTable(SSTable *T);
Status Search (SSTable *T);

int main()
{
    SSTable T;
    InitTable(&T);
    Search(&T);
}

Status InitTable(SSTable *T)
{
    T->length = 0;
    T->begin = NULL;

    char c = ' ';
    KeyType data;
    SElement *h, *t, *p;
    while (c != '\n')
    {
        scanf("%d", &data);
        if (!T->begin)
        {
            h = (SElement*)malloc(sizeof(SElement));
            T->begin = h;
            h->key = data;
            h->next_key = h;
            p = h;
        }
        else
        {
            t = (SElement*)malloc(sizeof(SElement));
            t->key = data;
            t->next_key = h;
            p->next_key = t;
            p = t;
        }
        c = getchar();
    }
    return OK;
}

Status Search (SSTable *T)
{
    char c = ' ';
    KeyType data;
    SElement *h, *t;
    int flag;
    
    h = T->begin;
    t = T->begin;
    while (c != '\n')
    {
        flag = 0;
        scanf("%d", &data);
        if (data == t->key)
            flag = 1;
        else if (data > t->key)
        {
            SElement *tem = t;
            while(tem->next_key != h)
            {
                if (tem->key == data)
                {
                    flag = 1;
                    t = tem;
                    break;
                }
                else
                    tem = tem->next_key;
            }
            if (tem->key == data)
            {
                flag = 1;
                t = tem;
            }
        }
        else
        {
            SElement *tem = h;
            while(tem != t)
            {
                if (tem->key == data)
                {
                    flag = 1;
                    t = tem;
                    break;
                }
                else
                    tem = tem->next_key;
            }
            if (tem->key == data)
                flag = 1;
        }
        c = getchar();
        printf("%d", flag);
        if (c != '\n')
            printf(" ");
    }
    return OK;
}