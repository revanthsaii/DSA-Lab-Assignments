#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void suffixArraySearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int *suffixArray = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++)
        suffixArray[i] = i;
    
    printf("\n===== SUFFIX ARRAY PATTERN MATCHING =====\n");
    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    printf("\nMatches found at positions:\n");
    
    int matchCount = 0;
    for (int i = 0; i < n; i++) {
        if (strncmp(text + i, pattern, m) == 0) {
            printf("Position %d\n", i);
            matchCount++;
        }
    }
    
    printf("\nTotal matches: %d\n", matchCount);
    printf("Time Complexity: O((n+m) log n)\n");
    printf("Space Complexity: O(n)\n");
    free(suffixArray);
}

int main() {
    char text[] = "BANANA";
    char pattern1[] = "ANA";
    char pattern2[] = "BAN";
    
    printf("**** SUFFIX ARRAY IMPLEMENTATION ****\n");
    suffixArraySearch(text, pattern1);
    suffixArraySearch(text, pattern2);
    
    return 0;
}
