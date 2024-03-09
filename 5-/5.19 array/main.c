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

Status InitArray(Array *A, int dim);

int main()
{
    Array A;
    int *min_row, *max_col;
    int number = 0;
    Elemtype data;
    InitArray(&A, 2);
    for (int i = 0; i < A.bounds[0]; i++)
        for (int j = 0; j < A.bounds[1]; j++)
        {
            scanf("%d", &data);
            A.base[i * A.constants[0] + j] = data;
        }
    
    min_row = (int *)malloc(A.bounds[0] * sizeof(int));
    max_col = (int *)malloc(A.bounds[1] * sizeof(int));

    for (int i = 0; i < A.bounds[0]; i++)
    {
        int min = A.base[i * A.constants[0]];
        for (int j = 0; j < A.bounds[1]; j++)
            if (A.base[i * A.constants[0] + j * A.constants[1]] < min)
                min = A.base[i * A.constants[0] + j * A.constants[1]];
        min_row[i] = min;
    }

    for (int j = 0; j < A.bounds[1]; j++)
    {
        int max = A.base[j * A.constants[1]];
        for (int i = 0; i < A.bounds[0]; i++)
            if (A.base[j * A.constants[1] + i * A.constants[0]] > max)
                max = A.base[j * A.constants[1] + i * A.constants[0]];
        max_col[j] = max;
    }

    for (int i = 0; i < A.bounds[0]; i++)
        for (int j = 0; j < A.bounds[1]; j++)
            if (min_row[i] == max_col[j])
            {
                if (number == 0)
                    printf("%d", min_row[i]);
                else
                    printf(" %d", min_row[i]);
                number++;
            }
}

Status InitArray(Array *A, int dim)
{
    int elemotal, length;

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
        scanf("%d", &length);
        A->bounds[i] = length;
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