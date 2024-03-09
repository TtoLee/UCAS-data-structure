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
    int number = 0;
    Elemtype data;
    InitArray(&A, 2);
    for (int i = 0; i < A.bounds[0]; i++)
        for (int j = 0; j < A.bounds[1]; j++)
        {
            scanf("%d", &data);
            A.base[i * A.constants[0] + j * A.constants[1]] = data;
        }
    
    for (int i = A.bounds[0] - 1; i >= 0; i--)
        for (int j = A.bounds[1] - 1; j >= 0; j--)
        {
            if (A.base[i * A.constants[0] + j * A.constants[1]] != 0)
            {
                if (number != 0)
                    printf("+");
                if (A.base[i * A.constants[0] + j * A.constants[1]] != 1 || (i == 0 && j == 0))
                    printf("%d", A.base[i * A.constants[0] + j * A.constants[1]]);
                if (i != 0)
                    printf("xE%d", i);
                if (j != 0)
                    printf("yE%d", j);
                    number++;
            }
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