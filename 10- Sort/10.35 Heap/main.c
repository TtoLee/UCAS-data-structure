#include <stdio.h>
#include <limits.h>

#define ERROR 0
#define OK 1
#define MAXSIZE 10000

typedef int Status;
typedef struct Heap
{
    int data[MAXSIZE];
    int last;
} Heap;

Status CreateHeap (Heap *heap);
Status InsertHeap(Heap *heap, int data);
Status HeapAdjust(Heap *heap, int position);
Status PrintRoot(Heap *heap);
Status HeapSort(Heap *heap, int position);

int main()
{
    Heap heap;
    CreateHeap(&heap);
    while (heap.last)
    {
        PrintRoot(&heap);
        if (heap.last)
            printf (" ");
    }
}

Status CreateHeap (Heap *heap)
{
    int data = 0;
    char c = ' ';
    heap->last = 0;
    while (c != '\n')
    {
        scanf("%d", &data);
        c = getchar();
        InsertHeap(heap, data);
    }
    return OK;
}

Status InsertHeap(Heap *heap, int data)
{
    heap->data[heap->last] = data;
    heap->last++;
    HeapAdjust(heap, heap->last - 1);
    return OK;
}

Status HeapAdjust(Heap *heap, int position)
{
    if (position == 0)
        return OK;
    int parent = (position - 1) / 3;
    if (heap->data[position] < heap->data[parent])
    {
        int tem = heap->data[parent];
        heap->data[parent] = heap->data[position];
        heap->data[position] = tem;
        HeapAdjust(heap, parent);
    }
    return OK;
}

Status PrintRoot(Heap *heap)
{
    printf("%d", heap->data[0]);
    heap->data[0] = heap->data[--heap->last];
    HeapSort(heap, 0);
    return OK;
}

Status HeapSort(Heap *heap, int position)
{
    int min = INT_MAX;
    int p = 0;
    for (int i = 1; i <= 3; i++)
        if (position * 3 + i < heap->last && heap->data[position * 3 + i] < min)
        {
            min = heap->data[position * 3 + i];
            p = i;
        }
    if (p != 0 && min < heap->data[position])
    {
        int tem = heap->data[position];
        heap->data[position] = heap->data[3 * position + p];
        heap->data[3 * position + p] = tem;
        HeapSort(heap, position * 3 + p);
    }
    return OK;
}