#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 10
#define INT_COUNT 210

int main()
{
    FILE* fp;
    fopen_s(&fp, "entries.txt", "r");
    char str[MAX_STR_LEN] = { 0 };
    long nums[INT_COUNT] = { 0 };

    int numCount = 0;
    while (fgets(str, sizeof(str), fp) != NULL)
    {
        if (str[strlen(str) - 1] == '\n')
        {
            str[strlen(str) - 1] = '\0';
        }
        nums[numCount] = atoi(str);
        numCount++;
    }

    int isComplete = 0;

    for (int i = 0; i < numCount; i++)
    {
        if (isComplete == 1)
        {
            break;
        }
        for (int j = 0; j < numCount; j++)
        {
            if (isComplete == 1)
            {
                break;
            }
            for (int k = 0; k < numCount; k++)
            {
                if ((nums[i] + nums[j] + nums[k]) == 2020)
                {
                    printf("%d x %d x %d = %d\n", nums[i], nums[j], nums[k], (nums[i] * nums[j] * nums[k]));
                    isComplete = 1;
                    break;
                }
            }
        }
    }
    getchar();
}
