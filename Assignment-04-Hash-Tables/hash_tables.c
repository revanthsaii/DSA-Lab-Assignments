#include <stdio.h>
#include <string.h>
#define MAX 10

struct HashTable { char keys[MAX][20]; int values[MAX]; };

void insert(struct HashTable *ht, char *key, int value) {
    int idx = (key[0] - 'a') % MAX;
    strcpy(ht->keys[idx], key);
    ht->values[idx] = value;
    printf("Inserted %s -> %d\n", key, value);
}

int search(struct HashTable *ht, char *key) {
    int idx = (key[0] - 'a') % MAX;
    return strcmp(ht->keys[idx], key) == 0 ? ht->values[idx] : -1;
}

int main() {
    struct HashTable ht = {0};
    printf("\n===== HASH TABLE =====\n");
    insert(&ht, "apple", 10);
    insert(&ht, "banana", 20);
    insert(&ht, "cherry", 30);
    printf("Search apple: %d\n", search(&ht, "apple"));
    return 0;
}
