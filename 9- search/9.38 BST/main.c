#include <stdio.h>

#define MAX_TREE_SIZE 50

void merge(int *v, int n);

int main()
{
	int j, n, flag;
	int data[MAX_TREE_SIZE];
    char c = ' ';

    n = flag = 0;
    while ( c != '\n' || !flag)
    {
        if (c == '\n')
            flag = 1;
        int temp;
        scanf("%d", &temp);
        c = getchar();
        if (temp == -1)
            continue;
        data[n] = temp;
        n++;
    }

	merge(data, n);
	for (j = 0; j < n; ++j)
		printf("%d ", data[j]);
	return 0;
}

void merge(int *v, int n)
{
	int i, j, g;
	int t;

	for (g = n / 2; g > 0; g /= 2)
		for (i = g; i < n; i++)
			for (j = i - g; j >= 0 && v[j] > v[j + g]; j -= g)
			{
				t = v[j];
				v[j] = v[j + g];
				v[j + g] = t;
			}
}