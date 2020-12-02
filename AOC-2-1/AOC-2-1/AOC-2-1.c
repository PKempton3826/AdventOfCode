// File: AOC-2-1.c
// Project: AOC-2-1
// Programmer: Philip Kempton
// First Version: December 2nd, 2020
// Description: This file contains logic for solving the Advent of Code puzzle (day 2, puzzle 1).
//              Puzzle: Given a list of strings check if a specific character exists [range] number
//              of times in each string and count the correct strings. 
//              Example: "1-3 a: ababa" - password (ababa) must contains 1-3 a's.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define ERR_LEN 100 // max size of error string for errno
#define MAX_STR_LEN 50 // assumes no line in file will be above this in length

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

    // Open file for reading strings from
    if ((errNum = fopen_s(&fp, "passwords.txt", "r")) != 0)
    {
        // Error while opening file, display it and exit
        strerror_s(errStr, ERR_LEN, errNum);
        printf("File I/O error: %s", errStr);
        getAcknowledgement();
        return 0;
    }

    char str[MAX_STR_LEN] = { 0 }; // Will hold the string read from file
    char* remainder = 0; // Will hold remainder of parsed string
    char delim[] = "- :"; // Chars to split the string on
    char* buff; // Unused buffer for strtok_s call
    int validCount = 0; // Used to count the valid entries

    while (fgets(str, sizeof(str), fp) != NULL)
    {
        // Parse out the min, max, and char we're searching for
        int min = strtol(strtok_s(str, delim, &remainder), &buff, 10);
        int max = strtol(strtok_s(NULL, delim, &remainder), &buff, 10);
        char c = *(strtok_s(NULL, delim, &remainder));
        
        // Count the number of times the character is present
        int count = 0;
        while (*remainder != '\0')
        {
            if (*remainder == c)
            {
                count++;
            }
            remainder++;
        }

        // Check if the count is within our range
        if ((count >= min) && (count <= max))
        {
            validCount++;
        }
    }
    // Display result to user
    printf("%d good passwords found\n", validCount);
    getAcknowledgement();
}