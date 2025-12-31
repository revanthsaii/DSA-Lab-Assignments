#include <stdio.h>
#include <string.h>

#define PRIME 101
#define BASE 256

void rabinKarpSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int patternHash = 0, textHash = 0;
    int highestPow = 1;
    
    for (int i = 0; i < m - 1; i++)
        highestPow = (highestPow * BASE) % PRIME;
    
    for (int i = 0; i < m; i++) {
        patternHash = (patternHash * BASE + pattern[i]) % PRIME;
        textHash = (textHash * BASE + text[i]) % PRIME;
    }
    
    printf("\n===== RABIN-KARP PATTERN MATCHING =====\n");
    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    printf("\nMatches found at positions:\n");
    
    int matchCount = 0;
    for (int i = 0; i <= n - m; i++) {
        if (patternHash == textHash) {
            if (strncmp(text + i, pattern, m) == 0) {
                printf("Position %d\n", i);
                matchCount++;
            }
        }
        if (i < n - m) {
            textHash = (BASE * (textHash - text[i] * highestPow) + text[i + m]) % PRIME;
            if (textHash < 0)
                textHash += PRIME;
        }
    }
    
    printf("\nTotal matches: %d\n", matchCount);
    printf("Time Complexity: O(n+m) average\n");
    printf("Space Complexity: O(1)\n");
}

int main() {
    char text[] = "ABABDABABACABAB";
    char pattern1[] = "ABABDAB";
    char pattern2[] = "ABA";
    
    printf("**** RABIN-KARP ALGORITHM IMPLEMENTATION ****\n");
    rabinKarpSearch(text, pattern1);
    rabinKarpSearch(text, pattern2);
    return 0;
}
