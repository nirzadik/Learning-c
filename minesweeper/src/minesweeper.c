#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 5
#define COLS 5
#define MINES 10



void printBoard(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == -1) {
                printf(" * |");
            } else {
                printf(" %d |", board[i][j]);
            }
        }
        printf("\n");
    }
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void generateUniqueMines(int mines[]) {
    int i = 0;
    while (i < MINES) {
        int r = rand() % (ROWS * COLS);
        int duplicate = 0;
        for (int j = 0; j < i; j++) {
            if (mines[j] == r) {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) {
            mines[i] = r;
            i++;
        }
    }
    qsort(mines, MINES, sizeof(int), compare);
}


void initializeBoard(int board[ROWS][COLS]) {
    int minesCells[MINES];
    generateUniqueMines(minesCells);
    int mineCounter = 0;
    int placeCounter = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if(placeCounter == minesCells[mineCounter]) {
                board[i][j] = -1;
                mineCounter++;
            } else {
                board[i][j] = 0;
            }
            placeCounter++;
        }
    }
}

int calculateNeighbors(int board[ROWS][COLS], int row, int col) {
    int mineCount = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
                if (board[newRow][newCol] == -1) {
                    mineCount++;
                }
            }
        }
    }
    return mineCount;
}

void SetNeighborCounts(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] != -1) {
                board[i][j] = calculateNeighbors(board, i, j);
            }
        }
    }
}








int main(){
    srand(time(NULL));
    int board[ROWS][COLS];
    initializeBoard(board);
    printBoard(board);
    printf("\n");
    printf("\n");
    SetNeighborCounts(board);
    printBoard(board);
    // Further implementation goes here

    return 0;
}