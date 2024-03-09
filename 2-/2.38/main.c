#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define ERROR 0
#define OK 1

typedef int ElemType;
typedef int Status;
typedef struct node
{
    ElemType data;
    struct node *prior, *next;
    int freq, order;
}DoubleLinkList;

int order = 0;

DoubleLinkList* CreateDoubleLinkList (int n);
void Locate (DoubleLinkList *head, ElemType e);

int main()
{
    DoubleLinkList *L, *h;
    char c;
    int n, data;

    scanf ("%d", &n);

    L = CreateDoubleLinkList(n);
    h = L;

    scanf("%d", &data);
    Locate (L, data);
    while ((c = getchar()) != '\n')
    {
        scanf ("%d", &data);
        Locate (L, data);
    }
    
    h = L;
    for (int i = 0; i < n; i++)
    {
        h = h->next;
        printf("%d ", (*h).data);
    }
}

DoubleLinkList* CreateDoubleLinkList (int n)
{
    DoubleLinkList *head, *p, *s;
    int i;

    head = (DoubleLinkList*)malloc(sizeof(DoubleLinkList));
    p = head;
    for (i = 1; i<=n; i++)
    {
        s = (DoubleLinkList*)malloc(sizeof(DoubleLinkList));
        scanf("%d", &s->data);
        (*s).prior = p;
        (*p).next = s;
        (*s).freq = 0;
        (*s).order = 0;
        p = s;
    }
    (*p).next = head;
    (*head).prior = p;
    return head;
}

void Locate (DoubleLinkList *head, ElemType e)
{
    DoubleLinkList *p, *r, *tag;
    tag = head->next;
    while (tag != head)
    {
        tag = tag->next;
        if (tag->prior->data == e)
        {
            p = tag->prior;
            p->freq++;
            if (p->order == 0)
                p->order = ++order;
            while (p->prior != head && p->prior->freq <= p->freq)
            {
                if(p->prior->freq == p->freq && p->prior->order < p->order)
                    break;
                else
                {
                    r = p->prior;
                    r->prior->next = p;
                    p->next->prior = r;
                    p->prior = r->prior;
                    r->prior = p;
                    r->next = p->next;
                    p->next = r;
                }
            }
        }
    }
}
