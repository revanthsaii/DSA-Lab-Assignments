#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHAR_SET 256

void buildBadCharTable(char *pattern, int m, int badChar[]) {
    for (int i = 0; i < CHAR_SET; i++)
        badChar[i] = -1;
    for (int i = 0; i < m; i++)
        badChar[(int)pattern[i]] = i;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void boyerMooreSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int badChar[CHAR_SET];
    buildBadCharTable(pattern, m, badChar);
    
    int i = 0;
    printf("\n===== BOYER-MOORE PATTERN MATCHING =====\n");
    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    printf("\nMatches found at positions:\n");
    
    int matchCount = 0;
    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[i + j])
            j--;
        
        if (j < 0) {
            printf("Position %d\n", i);
            matchCount++;
            i += (i + m < n) ? m - badChar[(int)text[i + m]] : 1;
        } else {
            i += max(1, j - badChar[(int)text[i + j]]);
        }
    }
    
    printf("\nTotal matches: %d\n", matchCount);
    printf("Time Complexity: O(n/m) best, O(nm) worst\n");
    printf("Space Complexity: O(k) where k = alphabet size\n");
}

int main() {
    char text[] = "ABCCDDAEFGGHII";
    char pattern1[] = "GGH";
    char pattern2[] = "AE";
    
    printf("\n**** BOYER-MOORE ALGORITHM IMPLEMENTATION ****\n");
    boyerMooreSearch(text, pattern1);
    boyerMooreSearch(text, pattern2);
    return 0;
}
