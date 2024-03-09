#include <stdio.h>
#include <malloc.h>

typedef int Status;
typedef int Elemtype;
typedef struct{
    Elemtype *base;
    int dim;
    int *bounds;
    int *constants;
}Array;

#define ERROR 0
#define OK 1
#define MAX_ARRAR_DIM 10

Status InitArray(Array *A, int dim, int length[]);

int main()
{
    Array A, B, C;
    int *a_data, *b_data;
    int number;
    int length[2];
    int len_a, len_b, cur_a, cur_b;
    Elemtype data;
    char c;

    cur_a = 0;
    cur_b = 0;

    for (int i = 0; i < 2; i++)
        scanf("%d", &length[i]);
    
    InitArray(&A, 2, length);
    InitArray(&B, 2, length);
    InitArray(&C, 2, length);

    scanf("%d", &data);
    if (data != 0)
    {
        len_a = 1;
        a_data = (int *)malloc(sizeof(int));
        a_data[0] = data;
        while ((c = getchar()) != '\n')
        {
            scanf("%d", &data);
            a_data = (int *)realloc(a_data, (len_a + 1) * sizeof(int));
            a_data[len_a] = data;
            len_a++;
        }
        for (int i = 0; i < A.bounds[0]; i++)
            for (int j = 0; j < A.bounds[1]; j++)
        {
            scanf("%d", &data);
            A.base[i * A.constants[0] + j * A.constants[1]] = data;
        }
    }
    else
    {
        for (int i = 0; i < A.bounds[0]; i++)
            for (int j = 0; j < A.bounds[1]; j++)
            {
                if (i || j)
                    scanf("%d", &data);
                A.base[i * A.constants[0] + j * A.constants[1]] = 0;
            }
    }

    scanf("%d", &data);
    if (data != 0)
    {
        len_b = 1;
        b_data = (int *)malloc(sizeof(int));
        b_data[0] = data;
        while ((c = getchar()) != '\n')
        {
            scanf("%d", &data);
            b_data = (int *)realloc(b_data, (len_b + 1) * sizeof(int));
            b_data[len_b] = data;
            len_b++;
        }
        for (int i = 0; i < B.bounds[0]; i++)
            for (int j = 0; j < B.bounds[1]; j++)
        {
            scanf("%d", &data);
            B.base[i * B.constants[0] + j * B.constants[1]] = data;
        }
    }
    else
    {
        for (int i = 0; i < B.bounds[0]; i++)
            for (int j = 0; j < B.bounds[1]; j++)
            {
                if (i || j)
                    scanf("%d", &data);
                B.base[i * B.constants[0] + j * B.constants[1]] = 0;
            }
    }

    for (int i = 0; i < C.bounds[0]; i++)
    {
        for (int j = 0; j < C.bounds[1]; j++)
        {
            if (A.base[i * A.constants[0] + j * A.constants[1]] && B.base[i * B.constants[0] + j * B.constants[1]])
            {
                C.base[i * C.constants[0] + j * C.constants[1]] = a_data[cur_a] + b_data[cur_b];
                cur_a++;
                cur_b++;
            }
            else if (A.base[i * A.constants[0] + j * A.constants[1]])
            {
                C.base[i * C.constants[0] + j * C.constants[1]] = a_data[cur_a];
                cur_a++;
            }
            else if (B.base[i * B.constants[0] + j * B.constants[1]])
            {
                C.base[i * C.constants[0] + j * C.constants[1]] = b_data[cur_b];
                cur_b++;
            }
            else
                C.base[i * C.constants[0] + j * C.constants[1]] = 0;
        }
    }
    
    number = 0;
    for (int i = 0; i < C.bounds[0]; i++)
    {
        for (int j = 0; j < C.bounds[1]; j++)
        {
            if (C.base[i * C.constants[0] + j * C.constants[1]])
            {
                if (!number)
                {
                    printf("%d", C.base[i * C.constants[0] + j * C.constants[1]]);
                    number++;
                }
                else
                {
                    printf(" %d", C.base[i * C.constants[0] + j * C.constants[1]]);
                    number++;
                }
            }
        }

    }
    printf("\n");

    for (int i = 0; i < C.bounds[0]; i++)
    {
        for (int j = 0; j < C.bounds[1]; j++)
        {
            if (C.base[i * C.constants[0] + j * C.constants[1]])
                number = 1;
            else
                number = 0;
            
            if (j == 0)
                printf("%d", number);
            else
                printf(" %d", number);
        }
        if (i != C.bounds[0])
        printf("\n");
    }
}

Status InitArray(Array *A, int dim, int length[])
{
    int elemotal;

    if (dim < 1 || dim > MAX_ARRAR_DIM)
        return ERROR;
    A->dim = dim;

    A->bounds = (int *)malloc(dim * sizeof(int));
    A->constants = (int *)malloc(dim * sizeof(int));
    if (!A->bounds)
        return ERROR;
    elemotal = 1;
    for (int i = 0; i < dim; i++)
    {
        A->bounds[i] = length[i];
        if (A->bounds[i] <= 0)
            return ERROR;
        elemotal *= A->bounds[i];
    }

    A->base = (Elemtype *)malloc(elemotal * sizeof(Elemtype));
    if (!A->base)
        return ERROR;
    A->constants[dim-1] = 1;
    for (int i = dim-2; i >= 0; i--)
        A->constants[i] = A->bounds[i+1] * A->constants[i+1];
    return OK;
}