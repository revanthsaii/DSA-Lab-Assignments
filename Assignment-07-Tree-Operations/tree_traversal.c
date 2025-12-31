#include <stdio.h>
#include <stdlib.h>

// Binary Tree Node
struct Node {
  int data;
  struct Node *left, *right;
};

// Create a new node
struct Node *create(int x) {
  struct Node *n = malloc(sizeof(struct Node));
  n->data = x;
  n->left = n->right = NULL;
  return n;
}

// Inorder Traversal: Left -> Root -> Right
void inorder(struct Node *r) {
  if (!r) return;
  inorder(r->left);
  printf("%d ", r->data);
  inorder(r->right);
}

// Preorder Traversal: Root -> Left -> Right
void preorder(struct Node *r) {
  if (!r) return;
  printf("%d ", r->data);
  preorder(r->left);
  preorder(r->right);
}

// Postorder Traversal: Left -> Right -> Root
void postorder(struct Node *r) {
  if (!r) return;
  postorder(r->left);
  postorder(r->right);
  printf("%d ", r->data);
}

int main() {
  // Create binary tree
  struct Node *root = create(1);
  root->left = create(2);
  root->right = create(3);
  root->left->left = create(4);
  root->left->right = create(5);

  printf("===== BINARY TREE TRAVERSALS =====\n\n");
  printf("Tree Structure:\n");
  printf("       1\n");
  printf("      / \\\n");
  printf("     2   3\n");
  printf("    / \\\n");
  printf("   4   5\n\n");

  printf("Inorder Traversal (Left->Root->Right):\n");
  inorder(root);
  printf("\n");
  printf("Expected: 4 2 5 1 3\n\n");

  printf("Preorder Traversal (Root->Left->Right):\n");
  preorder(root);
  printf("\n");
  printf("Expected: 1 2 4 5 3\n\n");

  printf("Postorder Traversal (Left->Right->Root):\n");
  postorder(root);
  printf("\n");
  printf("Expected: 4 5 2 3 1\n\n");

  printf("Time Complexity: O(n) for all traversals\n");
  printf("Space Complexity: O(h) where h is height (recursion stack)\n");
  printf("\nTraversal Methods:\n");
  printf("1. Inorder: Used for binary search trees (produces sorted output)\n");
  printf("2. Preorder: Used for creating prefix expressions\n");
  printf("3. Postorder: Used for deleting trees and suffix expressions\n");

  return 0;
}
