#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define MAX_Word_SIZE 100

typedef int Status;
typedef struct word
{
    int tag;
    int begin;
    int size;
    struct word *next_word;
} word;
typedef struct mem
{
    word *first_free_word;
    int free_block_num;
} mem;

Status InitMemory(mem *memory);
Status GetFreeBlock(mem *memory);
Status RecycleBlock(mem *memory);
Status PrintBlock (mem memory);

int main()
{
    mem memory;
    InitMemory(&memory);
    GetFreeBlock(&memory);
    RecycleBlock(&memory);
    PrintBlock(memory);
}

Status InitMemory(mem *memory)
{
    (*memory).first_free_word = NULL;
    (*memory).free_block_num = 0;
}

Status GetFreeBlock(mem *memory)
{
    char c;
    int begin, size;
    word *block, *insert;

    while((c = getchar()) != '\n')
    {
        scanf("%d %d", &begin, &size);
        block = (word*)malloc(sizeof(word));
        block->begin = begin;
        block->size = size;
        block->tag = 0;
        insert = memory->first_free_word;
        if (!insert || begin < insert->begin)
        {
            block->next_word = insert;
            memory->first_free_word = block;
        }
        else
        {
            while (insert->next_word && insert->next_word->begin < begin)
                insert = insert->next_word;
            block->next_word = insert->next_word;
            insert->next_word = block;
        }
        memory->free_block_num++;
        getchar();
    }
    return OK;
}

Status RecycleBlock(mem *memory)
{
    char c;
    int begin, size;
    word *block, *insert;

    while((c = getchar()) != EOF)
    {
        scanf("%d %d", &begin, &size);
        block = (word*)malloc(sizeof(word));
        block->begin = begin;
        block->size = size;
        block->tag = 0;
        insert = memory->first_free_word;
        if (!insert)
        {
            block->next_word = insert;
            memory->first_free_word = block;
            memory->free_block_num++;
        }
        else if (begin < insert->begin)
        {
            if (begin + size == insert->begin)
            {
                insert->begin = begin;
                insert->size += size;
            }
            else
            {
                block->next_word = insert;
                memory->first_free_word = block;
                memory->free_block_num++;
            }
        }
        else
        {
            while (insert->next_word && insert->next_word->begin < begin)
                insert = insert->next_word;
            if (begin == insert->begin + insert->size || insert->next_word && begin + size == insert->next_word->begin)
            {
                if (begin == insert->begin + insert->size)
                {
                    insert->size += size;
                    if (insert->next_word && begin + size == insert->next_word->begin)
                    {
                        insert->size += insert->next_word->size;
                        word *next = insert->next_word;
                        insert->next_word = insert->next_word->next_word;
                        free(next);
                        memory->free_block_num--;
                    }
                }
                else
                {
                    insert->next_word->size += block->size;
                    insert->next_word->begin = block->begin;
                    memory->free_block_num++;
                }
            }
            else
            {
                block->next_word = insert->next_word;
                insert->next_word = block;
            }
        }
        getchar();
    }
    return OK;
}

Status PrintBlock (mem memory)
{
    word *out = memory.first_free_word;
    while (out)
    {
        printf("%d %d %d",out->tag, out->begin, out->size);
        out = out->next_word;
        if (out)
            printf("\n");
    }
    return OK;
}