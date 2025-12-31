#include <stdio.h>
#include <string.h>

#define MAX 100

// Fibonacci using Memoization
int fib_memo[MAX];

int fibonacci(int n) {
    if (n <= 1) return n;
    if (fib_memo[n] != -1) return fib_memo[n];
    return fib_memo[n] = fibonacci(n-1) + fibonacci(n-2);
}

// 0/1 Knapsack Problem
int knapsack(int capacity, int weights[], int values[], int n) {
    int dp[n+1][capacity+1];
    memset(dp, 0, sizeof(dp));
    
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i-1] <= w)
                dp[i][w] = max(values[i-1] + dp[i-1][w-weights[i-1]], dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    return dp[n][capacity];
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Longest Common Subsequence
int lcs(char *s1, char *s2) {
    int m = strlen(s1), n = strlen(s2);
    int dp[m+1][n+1];
    memset(dp, 0, sizeof(dp));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[m][n];
}

// Coin Change Problem
int coinChange(int coins[], int n, int amount) {
    int dp[amount+1];
    for (int i = 0; i <= amount; i++) dp[i] = amount + 1;
    dp[0] = 0;
    
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i)
                dp[i] = min(dp[i], 1 + dp[i - coins[j]]);
        }
    }
    return dp[amount] > amount ? -1 : dp[amount];
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    printf("===== DYNAMIC PROGRAMMING SOLUTIONS =====\n\n");
    
    // Fibonacci
    printf("1. Fibonacci(10) = ");
    memset(fib_memo, -1, sizeof(fib_memo));
    printf("%d\n\n", fibonacci(10));
    
    // Knapsack
    printf("2. 0/1 Knapsack:\n");
    int weights[] = {2, 3, 5, 7};
    int values[] = {10, 20, 30, 40};
    int capacity = 10;
    printf("Max Value: %d\n\n", knapsack(capacity, weights, values, 4));
    
    // LCS
    printf("3. LCS(\"ABCDGH\", \"AEDFHR\") = %d\n\n", lcs("ABCDGH", "AEDFHR"));
    
    // Coin Change
    printf("4. Coin Change:\n");
    int coins[] = {1, 2, 5};
    printf("Min coins for amount 5: %d\n", coinChange(coins, 3, 5));
    
    return 0;
}
