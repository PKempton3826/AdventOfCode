// File: AOC-1-1.c
// Project: AOC-1-1
// Programmer: Philip Kempton
// First Version: December 1st, 2020
// Description: This file contains logic for solving the Advent of Code puzzle (day 1, puzzle 1).
//              Puzzle: Given a list of integers, find the product of 2 of them whose sum is 2020.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 6 // Assumes that no number in the file has more than 5 digits
#define NUM_COUNT 250 // Assumes that no more than 250 numbers are in the file
#define GOAL 2020 // Summation goal to reach

int main()
{
    FILE* fp;
    fopen_s(&fp, "entries.txt", "r");
    char str[MAX_STR_LEN] = { 0 };
    int nums[NUM_COUNT] = { 0 };

    // Read all numbers from file into array
    int numCount = 0;
    while (fgets(str, sizeof(str), fp) != NULL)
    {
        if (str[strlen(str) - 1] == '\n')
        {
            // Trim off the newline char left by fgets, if it exists
            str[strlen(str) - 1] = '\0';
        }
        nums[numCount] = atoi(str);
        numCount++;
    }

    // Loop through all numbers, checking if any add up to our goal
    // This isn't very efficient, will have O(N^2) time complexity
    for (int i = 0; i < numCount; i++)
    {
        for (int j = 0; j < numCount; j++)
        {
            if ((nums[i] + nums[j]) == GOAL)
            {
                // Found a winning combo
                printf("%d + %d = %d\n", nums[i], nums[j], (nums[i] + nums[j]));
                printf("%d x %d = %d\n", nums[i], nums[j], ((long)nums[i] * (long)nums[j]));
                i = NUM_COUNT; // Sort of a hack but this will break out of top loop (i)
                break;
            }
        }
    }
    printf("\nPress any key to continue...\n");
    getch();
}