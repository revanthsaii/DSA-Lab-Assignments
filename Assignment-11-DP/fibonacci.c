#include <stdio.h>
#include <string.h>

#define MAX 100

// Fibonacci using Memoization (Top-down DP)
int fib_memo[MAX];

int fibonacci(int n) {
  if (n <= 1) return n;
  if (fib_memo[n] != -1) return fib_memo[n];
  return fib_memo[n] = fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
  // Initialize memoization array
  memset(fib_memo, -1, sizeof(fib_memo));

  printf("===== FIBONACCI SEQUENCE (Memoization) =====\n");
  printf("Input: n = 10\n");

  int n = 10;
  int result = fibonacci(n);
  printf("Fibonacci(%d) = %d\n\n", n, result);

  printf("DP Table:\n");
  memset(fib_memo, -1, sizeof(fib_memo));
  for (int i = 0; i <= n; i++) {
    printf("F(%d) = %d\n", i, fibonacci(i));
  }

  printf("\nSequence: ");
  for (int i = 0; i <= n; i++) {
    printf("%d", fib_memo[i]);
    if (i < n) printf(", ");
  }
  printf("\n\n");

  printf("Time Complexity: O(n)\n");
  printf("Space Complexity: O(n)\n");
  printf("Approach: Top-down DP with Memoization\n");

  return 0;
}
