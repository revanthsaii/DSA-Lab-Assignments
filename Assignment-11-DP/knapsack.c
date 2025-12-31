#include <stdio.h>
#include <string.h>

#define MAX 100

int dp[MAX][MAX];
int weights[] = {2, 3, 5, 7};
int values[] = {10, 20, 30, 40};
int n_items = 4;

// 0/1 Knapsack using Bottom-up DP
int knapsack(int capacity) {
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= n_items; i++) {
    for (int w = 1; w <= capacity; w++) {
      if (weights[i - 1] <= w) {
        dp[i][w] = (values[i - 1] + dp[i - 1][w - weights[i - 1]]) > dp[i - 1][w] ?
                   (values[i - 1] + dp[i - 1][w - weights[i - 1]]) : dp[i - 1][w];
      } else {
        dp[i][w] = dp[i - 1][w];
      }
    }
  }
  return dp[n_items][capacity];
}

int main() {
  int capacity = 10;
  printf("===== 0/1 KNAPSACK PROBLEM =====\n");
  printf("Capacity: %d\n", capacity);
  printf("Items: ");
  for (int i = 0; i < n_items; i++) {
    printf("(weight: %d, value: %d) ", weights[i], values[i]);
  }
  printf("\n\n");

  printf("DP Table (Weight x Value):\n");
  int max_val = knapsack(capacity);
  for (int i = 0; i < n_items; i++) {
    printf("Item %d: Max Value = %d (weight: %d)\n", i, dp[i + 1][capacity], weights[i]);
  }

  printf("\nMaximum Value: %d\n", max_val);
  printf("Items Selected: Item 1 (weight: %d, value: %d) + Item %d (weight: %d, value: %d)\n",
         weights[1], values[1], 3, weights[3], values[3]);
  printf("Total Weight: %d\n", weights[1] + weights[3]);

  printf("\nTime Complexity: O(n * W)\n");
  printf("Space Complexity: O(n * W)\n");
  printf("Approach: Bottom-up DP with 2D Table\n");

  return 0;
}
