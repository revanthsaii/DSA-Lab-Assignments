#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void buildZArray(char *str, int *z) {
    int n = strlen(str);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r)
            z[i] = (z[i - l] < r - i + 1) ? z[i - l] : r - i + 1;
        while (i + z[i] < n && str[z[i]] == str[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
}

void zAlgorithmSearch(char *text, char *pattern) {
    char *combined = (char *)malloc((strlen(text) + strlen(pattern) + 2) * sizeof(char));
    sprintf(combined, "%s$%s", pattern, text);
    int n = strlen(combined);
    int m = strlen(pattern);
    int *z = (int *)malloc(n * sizeof(int));
    buildZArray(combined, z);
    
    printf("\n===== Z-ALGORITHM PATTERN MATCHING =====\n");
    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    printf("\nMatches found at positions:\n");
    
    int matchCount = 0;
    for (int i = m + 1; i < n; i++)
        if (z[i] == m) {
            printf("Position %d\n", i - m - 1);
            matchCount++;
        }
    
    printf("\nTotal matches: %d\n", matchCount);
    printf("Time Complexity: O(n+m)\n");
    printf("Space Complexity: O(n+m)\n");
    free(z);
    free(combined);
}

int main() {
    char text[] = "ABABDABABACABAB";
    char pattern1[] = "ABA";
    char pattern2[] = "ABAB";
    
    printf("**** Z-ALGORITHM IMPLEMENTATION ****\n");
    zAlgorithmSearch(text, pattern1);
    zAlgorithmSearch(text, pattern2);
    return 0;
}
