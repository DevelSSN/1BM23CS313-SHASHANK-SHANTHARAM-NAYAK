#include <stdio.h>
#include <stdbool.h>

#define N 4

bool isSafe(int board[], int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || 
            board[i] - i == col - row || 
            board[i] + i == col + row) {
            return false;
        }
    }
    return true;
}

void printSolution(int board[]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j) {
                printf("Q ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

bool solveNQueens(int board[], int row) {
    if (row == N) {
        printSolution(board);
        return true;
    }

    bool res = false;
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            res = solveNQueens(board, row + 1) || res;
            board[row] = -1;
        }
    }
    return res;
}

int main() {
    int board[N];
    for (int i = 0; i < N; i++) {
        board[i] = -1;
    }

    if (!solveNQueens(board, 0)) {
        printf("No solution exists.\n");
    }

    return 0;
}
