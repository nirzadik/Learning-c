#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 5
#define COLS 5
#define MINES 2

typedef struct
{
    int row;
    int col;
    int flag;
}point;





void printBoard(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        printf("|");
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

void printUserBoard(int userBoard[ROWS][COLS], int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        printf("|");
        for (int j = 0; j < COLS; j++) {
            switch (userBoard[i][j])
            {
            case -1: // flagged
                printf(" F |");
                break;
            case 0: // hidden
                printf(" 0 |");
                break;
            case 1: // revealed
                if (board[i][j] == 0){
                    printf("   |");
                }
                else {
                    printf(" %d |", board[i][j]);
                }
                break;
            default:
                break;
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

void initializeUserBoard(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = 0;
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
    SetNeighborCounts(board);
}

point getUserMove() {
    char line[4];
    point p;
    printf("Enter reveal row: ");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &p.row);
    printf("Enter reveal col: ");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &p.col);
    while (p.row < 0 || p.row >= ROWS || p.col < 0 || p.col >= COLS) {
        printf("Invalid input. Please enter values between 0 and %d for rows and 0 and %d for columns.\n", ROWS - 1, COLS - 1);
        printf("Enter reveal row: ");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &p.row);
        printf("Enter reveal col: ");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &p.col);
    }
    printf("if you want to flag this cell, enter 1, enter 2 to un-flag, else enter 0: ");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &p.flag);
    return p;
}

void revealZeros(int userBoard[ROWS][COLS], int board[ROWS][COLS], int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        return;
    }
    if (userBoard[row][col] != 0) {
        return;
    }
    userBoard[row][col] = 1; // Mark as revealed
    if (board[row][col] == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i != 0 || j != 0) {
                    revealZeros(userBoard, board, row + i, col + j);
                }
            }
        }
    }
}

int setUserReveale(int userBoard[ROWS][COLS], int board[ROWS][COLS]) {
    point p = getUserMove();
    printf("CHECK: board place: %d\n", board[p.row][p.col]);
    if (p.flag == 2)
    {
        if(userBoard[p.row][p.col] != -1){
            printf("Cannot un-flag a non-flagged cell. Choose another cell.\n");
            p = getUserMove();
        }
        else{
            userBoard[p.row][p.col] = 0; // Un-flag the cell
            return 0;
        }
    }
    while (userBoard[p.row][p.col] != 0)
    {
        printf("Cell already revealed or flagged. Choose another cell.\n");
        p = getUserMove();
    }
    if (p.flag == 1)
    {
        userBoard[p.row][p.col] = -1; // Mark as flagged
        return 0;
    }
    if (board[p.row][p.col] > 0){
        userBoard[p.row][p.col] = 1; // Mark as revealed
    }
    else if (board[p.row][p.col] == 0){
        revealZeros(userBoard, board, p.row, p.col);
    }
    else if (board[p.row][p.col] == -1){
        return -1; // Hit a mine
    }
    return 0;
}

int checkWin(int userBoard[ROWS][COLS], int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] != -1 && userBoard[i][j] != 1) {
                return 0; // Not all non-mine cells are revealed
            }
        }
    }
    return 1; // All non-mine cells are revealed
}



int main(){
    srand(time(NULL));
    int board[ROWS][COLS];
    int userBoard[ROWS][COLS];
    initializeBoard(board);
    initializeUserBoard(userBoard);
    printf("welcome to the game!\n");
    printUserBoard(userBoard, board);
    printf("\n");
    do{  
        if (setUserReveale(userBoard, board) == -1) {
            goto gameOver;
        }
        printUserBoard(userBoard, board);
        printf("\n");
    } while (!checkWin(userBoard, board));
    printf("Congratulations! you won!\n");
    return 0;


    gameOver:
        printf("Game Over! you lost!\n");
        printBoard(board);
    return 0;
}