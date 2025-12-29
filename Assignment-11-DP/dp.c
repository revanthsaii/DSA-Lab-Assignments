#include <stdio.h>
int fib(int n, int memo[]) { if(n<=1) return n; if(memo[n]!=-1) return memo[n]; return memo[n]=fib(n-1,memo)+fib(n-2,memo); }
int main() { int n=10; int memo[11]; for(int i=0;i<=n;i++) memo[i]=-1; printf("\n===== DYNAMIC PROGRAMMING (FIBONACCI) =====\n"); printf("Fibonacci Sequence:\n"); for(int i=0;i<=n;i++) printf("%d ",fib(i,memo)); printf("\n"); return 0; }
