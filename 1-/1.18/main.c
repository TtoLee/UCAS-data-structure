#include <stdio.h>

#define MEMBER_SIZE 5
#define MALE 0
#define FEMALE 1
#define TOTAL 2

int main()
{
    char c;
    char sex, school;
    int pro_score;
    int table[MEMBER_SIZE][3];
    for (int i = 0; i < MEMBER_SIZE; i++)
        for (int j = 0; j < 3; j++)
            table[i][j] = 0;

    while ((c = getchar()) != EOF)
    {
        while ((c = getchar()) != ' ') ;
        scanf("%c %c %d", &sex, &school, &pro_score);
        getchar();
        if (sex == 'M')
        {
            table[school-'A'][MALE] += pro_score;
            table[school-'A'][TOTAL] += pro_score;
        }
        else if (sex == 'F')
        {
            table[school-'A'][FEMALE] += pro_score;
            table[school-'A'][TOTAL] += pro_score;            
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (table[i][j] == 0)
                continue;
            else switch (j)
            {
            case 0:
                printf("%c M %d\n", i+'A', table[i][j]);
                break;
            case 1:
                printf("%c F %d\n", i+'A', table[i][j]);
                break;
            case 2:
                printf("%c %d\n", i+'A', table[i][j]);
                break;
            default:
                break;
            }
        }
    }
}