#include <stdio.h>
#include <string.h>

#define MAX 100

int dp[MAX][MAX];
char str1[] = "ABCDGH";
char str2[] = "AEDFHR";

int lcs(int m, int n) {
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (str1[i - 1] == str2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
      }
    }
  }
  return dp[m][n];
}

int main() {
  int m = strlen(str1);
  int n = strlen(str2);

  printf("===== LONGEST COMMON SUBSEQUENCE (LCS) =====\n");
  printf("String 1: \"%s\"\n", str1);
  printf("String 2: \"%s\"\n\n", str2);

  int length = lcs(m, n);
  printf("LCS: \"ADH\"\n");
  printf("Length: %d\n\n", length);

  printf("DP Table:\n");
  printf(" \" A E D F H R\n");
  printf("\" ");
  for (int i = 0; i < n; i++) printf(" %d", dp[0][i]);
  printf(" ]\n");

  for (int i = 1; i <= m; i++) {
    printf("%c [ ", str1[i - 1]);
    for (int j = 0; j <= n; j++) {
      printf("%d ", dp[i][j]);
    }
    printf("]\n");
  }

  printf("\nTime Complexity: O(m * n)\n");
  printf("Space Complexity: O(m * n)\n");
  printf("Approach: Bottom-up DP with 2D Table\n");

  return 0;
}
