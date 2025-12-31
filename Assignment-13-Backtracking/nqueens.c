#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

int board[N][N];
int solutionCount = 0;

// Check if placing queen at (r, c) is safe
int isSafe(int r, int c) {
    // Check if there's a queen in the same column
    for (int i = 0; i < r; i++) {
        if (board[i][c]) {
            return 0;
        }
    }
    
    // Check upper left diagonal
    for (int i = r, j = c; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return 0;
        }
    }
    
    // Check upper right diagonal
    for (int i = r, j = c; i >= 0 && j < N; i--, j++) {
        if (board[i][j]) {
            return 0;
        }
    }
    
    return 1;
}

// Print the current board configuration
void printSolution() {
    printf("\nSolution %d:\n", ++solutionCount);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Backtracking function to solve N-Queens
void solve(int r) {
    // Base case: all queens placed
    if (r == N) {
        printSolution();
        return;
    }
    
    // Try placing queen in each column of current row
    for (int c = 0; c < N; c++) {
        if (isSafe(r, c)) {
            board[r][c] = 1;        // Place queen
            solve(r + 1);            // Recur to next row
            board[r][c] = 0;         // Backtrack
        }
    }
}

int main() {
    printf("\n===== %d QUEENS PROBLEM =====\n", N);
    printf("Finding all possible solutions...\n");
    
    // Initialize board
    memset(board, 0, sizeof(board));
    
    // Solve the problem
    solve(0);
    
    printf("\nTotal Solutions Found: %d\n", solutionCount);
    printf("Time Complexity: O(N!)\n");
    printf("Space Complexity: O(N)\n");
    
    return 0;
}
