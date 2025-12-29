#include <stdio.h>
#include <math.h>

// Arithmetic Series: a, a+d, a+2d, ..., a+(n-1)d
int arithmeticSeries(int a, int d, int n) {
    return a * n + (d * n * (n - 1)) / 2;
}

// Geometric Series: a, a*r, a*r^2, ..., a*r^(n-1)
double geometricSeries(double a, double r, int n) {
    if (r == 1) return a * n;
    return a * (pow(r, n) - 1) / (r - 1);
}

// Sum of Natural Numbers: 1 + 2 + 3 + ... + n
int sumNatural(int n) {
    return n * (n + 1) / 2;
}

// Sum of Squares: 1^2 + 2^2 + ... + n^2
int sumSquares(int n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

int main() {
    printf("\n===== SERIES ANALYSIS =====\n");
    
    // Arithmetic Series
    printf("\nArithmetic Series: a=5, d=3, n=10\n");
    printf("Sum = %d\n", arithmeticSeries(5, 3, 10));
    
    // Geometric Series
    printf("\nGeometric Series: a=2, r=3, n=8\n");
    printf("Sum = %.2f\n", geometricSeries(2, 3, 8));
    
    // Natural Numbers
    printf("\nSum of Natural Numbers (1 to 100)\n");
    printf("Sum = %d\n", sumNatural(100));
    
    // Sum of Squares
    printf("\nSum of Squares (1^2 to 20^2)\n");
    printf("Sum = %d\n", sumSquares(20));
    
    return 0;
}
