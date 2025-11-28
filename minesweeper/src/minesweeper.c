#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 5
#define COLS 5
#define MINES 10

void initializeBoard(int board[ROWS][COLS]) {
    int mineCount = MINES;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = 0;
        }
    }
}
