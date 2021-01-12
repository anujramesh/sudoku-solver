#include <stdio.h>
#include <stdlib.h>

// The dimensions of the grid (ie 9x9)
#define SIZE 9

// A function to print the grid
void printGrid(int grid[SIZE][SIZE]) {
    int i;
    int j;

    for (i = 0; i < SIZE; i++) {

        for (j = 0; j < SIZE; j++) {
            printf("%d ", grid[i][j]);
        }

        printf("\n");

    }
}

// Checks if it is legal to assign a number to the given row, column
int isLegal(int grid[SIZE][SIZE], int row, int col, int num) {
    int i;

    // Check if number is present within the row; if it does, return 0
    for (i = 0; i < SIZE; i++) {
        if (grid[row][i] == num) {
            return 0;
        }
    }

    // Check if number is present within the column; if it is, return 0
    for (i = 0; i < SIZE; i++) {
        if (grid[i][col] == num) {
            return 0;
        }
    }

    // Check if number is present within the smaller 3x3 squares; if it is, return 0
    int startRow = row - row % (SIZE / 3); 
    int startCol = col - col % (SIZE / 3);

    for (int i = 0; i < (SIZE / 3); i++) {
        for (int j = 0; j < (SIZE / 3); j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return 0;
            }
        }
    }


    // If the number isn't present within the row, column, or square, it is legal: return 1
    return 1; 
}

int fillSudoku(int grid[SIZE][SIZE], int row, int col) {
    int i;

    // Checks if we reached 8th row and 9th col
    // Return 1 to avoid further backtracking
    if (row == (SIZE - 1) && col == SIZE) {
        return 1;
    }

    // Checks if column value equals the size of the grid
    // if it does, move to the next row, column "resets" back to 0
    if (col == SIZE) {
        row++;
        col = 0;
    }

    // Checks if current position of the grid already contains a value greater than 0
    if (grid[row][col] > 0) {
        return fillSudoku(grid, row, col + 1);
    }

    for (int num = 1; num <= SIZE; num++) {

        if (isLegal(grid, row, col, num)) {
            grid[row][col] = num;

            if (fillSudoku(grid, row, col + 1)) {
                return 1;
            }
        }

        grid[row][col] = 0;
    }

    return 0;
}

int main() {
    // 0 is used to represent "empty" squares

    int grid[SIZE][SIZE] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
			     { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
			     { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
			     { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
			     { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
			     { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
			     { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
			     { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
			     { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

    if (fillSudoku(grid, 0, 0)) {
        printGrid(grid);

    } else {
        printf("Solution does not exist.");
    }
}
