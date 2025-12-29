#include <stdio.h>

int moveCount = 0;

// Recursive function to solve Tower of Hanoi
void hanoi(int n, char source, char dest, char aux) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", source, dest);
        moveCount++;
        return;
    }
    hanoi(n-1, source, aux, dest);
    printf("Move disk %d from %c to %c\n", n, source, dest);
    moveCount++;
    hanoi(n-1, aux, dest, source);
}

int main() {
    int n = 4;
    printf("\n===== TOWER OF HANOI (n=%d) =====\n", n);
    printf("Moving %d disks from A to C using B as auxiliary\n\n", n);
    
    hanoi(n, 'A', 'C', 'B');
    
    printf("\nTotal moves: %d\n", moveCount);
    printf("Expected moves: %d\n", (1 << n) - 1);
    
    return 0;
}
