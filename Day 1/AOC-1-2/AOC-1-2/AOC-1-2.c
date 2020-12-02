// File: AOC-1-2.c
// Project: AOC-1-2
// Programmer: Philip Kempton
// First Version: December 1st, 2020
// Description: This file contains logic for solving the Advent of Code puzzle (day 1, puzzle 2).
//              Puzzle: Given a list of integers, find the product of 3 of them whose sum is 2020.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_STR_LEN 6 // Assumes that no number in the file has more than 5 digits
#define NUM_COUNT 250 // Assumes that no more than 250 numbers are in the file
#define GOAL 2020 // Summation goal to reach
#define ERR_LEN 100 // max size of error string for errno

// Function: getAcknowledgement
// Description: requests and waits for user to press Enter
// Parameters: n/a
// Returns: n/a
void getAcknowledgement()
{
    printf("\nPress [Enter] to exit\n");
    getchar(); // Intentionally ignore return
}

int main()
{
    FILE* fp;
    int errNum;
    char errStr[ERR_LEN];
    if ((errNum = fopen_s(&fp, "entries.txt", "r")) != 0)
    {
        // Error while opening file, display it and exit
        strerror_s(errStr, ERR_LEN, errNum);
        printf("File I/O error: %s", errStr);
        getAcknowledgement();
        return 0;
    }

    char str[MAX_STR_LEN] = { 0 };
    int nums[NUM_COUNT] = { 0 };

    // Read all numbers from file into array
    int numCount = 0;
    char* ptr;
    while (fgets(str, sizeof(str), fp) != NULL)
    {
        if (numCount >= NUM_COUNT)
        {
            // Too many numbers in txt file
            printf("Too many numbers in entries.txt (up to 250 allowed)\n");
            getAcknowledgement();
            return 0;
        }
        int buff = 0;
        if ((buff = strtol(str, &ptr, 10)) != 0)
        {
            nums[numCount] = buff;
        }
        else
        {
            // Invalid line in txt file
            printf("entries.txt has invalid text.  Only positive numbers should be present.\n");
            getAcknowledgement();
            return 0;
        }
        numCount++;
    }

    // Loop through all numbers, checking if any add up to our goal
    // This is fairly efficient, should be O(N^3) for time complexity
    for (int i = 0; i < numCount - 2; i++)
    {
        for (int j = i + 1; j < numCount - 1; j++)
        {
            for (int k = j + 1; k < numCount; k++)
            {
                if ((nums[i] + nums[j] + nums[k]) == GOAL)
                {
                    // Found a winning combo
                    printf("%d + %d + %d = %d\n", nums[i], nums[j], nums[k], (nums[i] + nums[j] + nums[k]));
                    printf("%d x %d x %d = %d\n", nums[i], nums[j], nums[k], ((long)nums[i] * (long)nums[j] * (long)nums[k]));
                    getAcknowledgement();
                    return 0;
                }
            }
        }
    }
    getAcknowledgement();
    return 0;
}
