// File: AOC-3-2.c
// Project: AOC-3-2
// Programmer: Philip Kempton
// First Version: December 3rd, 2020
// Description: This file contains logic for solving the Advent of Code puzzle (day 3, puzzle 2).
//              Puzzle: Given an area grid (area.txt) count how many trees are encountered using 
//                      various slopes and display the product of the results.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define ERR_LEN 100 // max size of error string for errno
#define AREA_WIDTH 31 // width of area grid in file
#define AREA_HEIGHT 323 // height of area grid in file
#define SLOPE_COUNT 5 // Number of slopes to check for trees

// Function: getAcknowledgement
// Description: requests and waits for user to press Enter.
// Parameters: n/a.
// Returns: n/a.
void getAcknowledgement()
{
    printf("\nPress [Enter] to exit\n");
    getchar(); // Intentionally ignore return
}

// Function: countTreesInPath
// Description: Counts trees hit when traversing an area, taking a specific path (slope).
//              This function only supports going down and to the right (toboganning down a hill).
// Parameters: 
//    area:   Area to traverse.
//    slopeRight: the x of the slope.
//    slopeDown:  the y of the slope (this should be positive, even though this function traverses 
//                down the area).
// Returns: Number of trees encountered.
long countTreesInPath(int area[AREA_HEIGHT][AREA_WIDTH], unsigned int slopeRight, unsigned int slopeDown)
{
    long treeCount = 0;
    int col = 0;
    for (int row = 0; row < AREA_HEIGHT; row += slopeDown)
    {
        if (area[row][col] == 1)
        {
            // Tree found
            treeCount++;
        }
        col += slopeRight;
        if (col >= AREA_WIDTH)
        {
            // Area has infinite width that repeats
            // We hit an edge, so go back to the beginning
            col -= AREA_WIDTH;
        }
    }
    return treeCount;
}

// Main
int main()
{
    FILE* fp;
    int errNum;
    char errStr[ERR_LEN];

    // Open file for reading strings from
    if ((errNum = fopen_s(&fp, "area.txt", "r")) != 0)
    {
        // Error while opening file, display it and exit
        strerror_s(errStr, ERR_LEN, errNum);
        printf("File I/O error: %s", errStr);
        getAcknowledgement();
        return 0;
    }

    // This will hold the area grid read from file
    int area[AREA_HEIGHT][AREA_WIDTH] = { 0 };

    // Convert the file content into the area array
    int i = 0;
    int j = 0;
    for (char c = getc(fp); c != EOF; c = getc(fp))
    {
        if (c == '.')
        {
            // Found an open spot
            area[j][i] = 0;
            i++;
        }
        else if (c == '#')
        {
            // Found a tree
            area[j][i] = 1;
            i++;
        }
        else if (c == '\n')
        {
            // Newline found, start next row
            j++;
            i = 0;
        }
    }

    // Array of slopes to check
    long slopes[SLOPE_COUNT][2] = {
        {1, 1},
        {3, 1},
        {5, 1},
        {7, 1},
        {1, 2},
    };

    // Check for trees using each slope, multiplying the results together as we go
    long product = 1;
    for (int i = 0; i < SLOPE_COUNT; i++)
    {
        product *= countTreesInPath(area, slopes[i][0], slopes[i][1]);
    }

    // Display result to user
    printf("%d is the product.\n", product);
    getAcknowledgement();
}
