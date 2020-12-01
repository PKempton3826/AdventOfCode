// File: AOC-1-1.c
// Project: AOC-1-1
// Programmer: Philip Kempton
// First Version: December 1st, 2020
// Description: This file contains logic for solving the Advent of Code puzzle (day 1, puzzle 1).
//              Puzzle: Given a list of integers, find the product of 2 of them whose sum is 2020.

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
    getchar();
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
        nums[numCount] = strtol(str, &ptr, 10);
        numCount++;
    }

    // Loop through all numbers, checking if any add up to our goal
    // This is fairly efficient, will have O(N^2) time complexity
    for (int i = 0; i < numCount - 1; i++)
    {
        for (int j = i + 1; j < numCount; j++)
        {
            if ((nums[i] + nums[j]) == GOAL)
            {
                // Found a winning combo
                printf("%d + %d = %d\n", nums[i], nums[j], (nums[i] + nums[j]));
                printf("%d x %d = %d\n", nums[i], nums[j], ((long)nums[i] * (long)nums[j]));
                getAcknowledgement();
                return 0;
            }
        }
    }
    printf("No valid combinations found\n");
    getAcknowledgement();
    return 0;
}