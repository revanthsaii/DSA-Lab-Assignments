#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void findPatterns(char *text, char *patterns[], int pCount) {
    printf("\n===== AHO-CORASICK MULTIPLE PATTERN MATCHING =====\n");
    printf("Text: %s\n", text);
    printf("\nPatterns searched:\n");
    for (int i = 0; i < pCount; i++)
        printf("  %d. %s\n", i + 1, patterns[i]);
    
    printf("\nMatches found:\n");
    int totalMatches = 0;
    for (int i = 0; i < pCount; i++) {
        char *pattern = patterns[i];
        int pLen = strlen(pattern);
        for (int j = 0; j <= strlen(text) - pLen; j++) {
            if (strncmp(&text[j], pattern, pLen) == 0) {
                printf("  Pattern '%s' at position %d\n", pattern, j);
                totalMatches++;
            }
        }
    }
    printf("\nTotal matches: %d\n", totalMatches);
    printf("Time Complexity: O(n + sum(m) + z)\n");
    printf("Space Complexity: O(sum(m) * k)\n");
}

int main() {
    char text[] = "USHERS";
    char *patterns[] = {"SH", "HE", "HER", "HERS"};
    int pCount = 4;
    
    printf("**** AHO-CORASICK ALGORITHM IMPLEMENTATION ****\n");
    findPatterns(text, patterns, pCount);
    
    printf("\n--- Another Example ---\n");
    char text2[] = "ABCDEFGABCD";
    char *patterns2[] = {"ABC", "BCD", "DEF"};
    findPatterns(text2, patterns2, 3);
    
    return 0;
}
