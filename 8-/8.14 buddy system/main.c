#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define ERROR 0
#define OK 1
#define MAX_Word_kval 100

typedef int Status;
typedef struct word
{
    int tag;
    int begin;
    struct word *next_word;
} word;
typedef struct mem
{
    word *first_free_word;
    int highbound;
    int lowbound;
    int size;
    int free_block_num;
} mem;

Status InitMemory(mem *memory);
Status PrintBlock (mem memory);

int main()
{
    mem memory;
    InitMemory(&memory);
    PrintBlock(memory);
}

Status InitMemory(mem *memory)
{
    (*memory).first_free_word = NULL;
    (*memory).free_block_num = 0;

    word *pre = NULL;
    scanf("%d %d %d", &memory->highbound, &memory->lowbound, &memory->size);

    for (int i = memory->highbound; i != memory->lowbound; i += memory->size)
    {
        word *block;
        block = (word*)malloc(sizeof(word));
        block->begin = i;
        block->next_word = NULL;
        scanf("%d", &block->tag);
        if (!pre)
            memory->first_free_word = block;
        else
            pre->next_word = block;
        pre = block;
        if (block->tag == 0)
            memory->free_block_num++;
    }
    return OK;
}

Status PrintBlock (mem memory)
{
    int number, begin;
    number = 0;
    word *out = memory.first_free_word;

    if (memory.free_block_num == 0)
    {
        printf("0 0 0");
        return OK;
    }
    for (int i = memory.highbound; i != memory.lowbound; i += memory.size)
    {
        if (out->tag == 0)
        {
            if (number == 0)
                begin = i;
            number++;
        }
        else
        {
            if (number != 0)
                printf("0 %d %d\n", begin, number * memory.size);
            number = 0;  
        }
        if (!out->next_word && number != 0)
            printf("0 %d %d\n", begin, number * memory.size);
        out = out->next_word;
    }
    return OK;
}