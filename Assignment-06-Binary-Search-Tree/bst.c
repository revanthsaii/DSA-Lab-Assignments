#include <stdio.h>
#include <stdlib.h>

// Binary Search Tree Node
struct Node {
  int data;
  struct Node *left, *right;
};

// Create a new node
struct Node *newNode(int x) {
  struct Node *n = malloc(sizeof(struct Node));
  n->data = x;
  n->left = n->right = NULL;
  return n;
}

// Insert a value into BST
struct Node *insert(struct Node *r, int x) {
  if (!r) return newNode(x);
  if (x < r->data) {
    r->left = insert(r->left, x);
  } else if (x > r->data) {
    r->right = insert(r->right, x);
  }
  return r;
}

// Search for a value in BST
bool search(struct Node *r, int x) {
  if (!r) return false;
  if (x == r->data) return true;
  if (x < r->data) return search(r->left, x);
  return search(r->right, x);
}

// Inorder traversal (Left -> Root -> Right)
void inorder(struct Node *r) {
  if (!r) return;
  inorder(r->left);
  printf("%d ", r->data);
  inorder(r->right);
}

int main() {
  // Create and insert values into BST
  struct Node *root = NULL;
  int arr[] = {50, 30, 70, 20, 40, 60, 80};
  int n = 7;

  printf("===== BINARY SEARCH TREE (BST) =====\n\n");
  printf("Inserting values: ");
  for (int i = 0; i < n; i++) {
    root = insert(root, arr[i]);
    printf("%d ", arr[i]);
  }
  printf("\n\n");

  printf("BST Structure (Inorder Traversal - Sorted):\n");
  inorder(root);
  printf("\n\n");

  printf("Searching Operations:\n");
  int search_vals[] = {40, 25, 60};
  for (int i = 0; i < 3; i++) {
    if (search(root, search_vals[i])) {
      printf(" %d found in BST\n", search_vals[i]);
    } else {
      printf(" %d not found in BST\n", search_vals[i]);
    }
  }

  printf("\nBST Properties:\n");
  printf("- Left subtree values < Parent value\n");
  printf("- Right subtree values > Parent value\n");
  printf("- All subtrees are also BSTs\n");
  printf("- No duplicate values\n\n");

  printf("Time Complexity (Balanced BST):\n");
  printf(" Insert: O(log n)\n");
  printf(" Search: O(log n)\n");
  printf(" Delete: O(log n)\n\n");

  printf("Space Complexity: O(h) where h is height\n");

  return 0;
}
