#include <stdio.h>
#include <string.h>

#define MAX 100
#define INF 9999

int dp[MAX];
int coins[] = {1, 2, 5};
int n_coins = 3;

int coinChange(int amount) {
  // Initialize DP array
  for (int i = 0; i <= amount; i++) {
    dp[i] = INF;
  }
  dp[0] = 0;

  // Fill DP table
  for (int i = 1; i <= amount; i++) {
    for (int j = 0; j < n_coins; j++) {
      if (coins[j] <= i) {
        dp[i] = (dp[i - coins[j]] + 1 < dp[i]) ? (dp[i - coins[j]] + 1) : dp[i];
      }
    }
  }
  return dp[amount];
}

int main() {
  int amount = 5;
  printf("===== COIN CHANGE PROBLEM =====\n");
  printf("Coins: ");
  for (int i = 0; i < n_coins; i++) {
    printf("[%d] ", coins[i]);
  }
  printf("\nAmount: %d\n\n", amount);

  int result = coinChange(amount);
  printf("Minimum Coins Needed: %d coin(s) (%d)\n\n", result, coins[2]);

  printf("DP Array:\n");
  for (int i = 0; i <= amount; i++) {
    printf("Amount %d: %d coins", i, dp[i]);
    if (i == 1) printf(" (%d)", coins[0]);
    else if (i == 2) printf(" (%d)", coins[1]);
    else if (i == 3) printf(" (2+%d)", coins[0]);
    else if (i == 4) printf(" (2+2)");
    else if (i == 5) printf(" (%d)", coins[2]);
    printf("\n");
  }

  printf("\nTime Complexity: O(n * amount)\n");
  printf("Space Complexity: O(amount)\n");
  printf("Approach: Bottom-up DP with 1D Array\n");

  return 0;
}
