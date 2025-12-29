#include <stdio.h>
#include <stdlib.h>
struct Node { int data; struct Node *left, *right; };
struct Node* create(int x) { struct Node* n = malloc(sizeof(struct Node)); n->data=x; n->left=n->right=NULL; return n; }
void inorder(struct Node* r) { if(!r) return; inorder(r->left); printf("%d ", r->data); inorder(r->right); }
void preorder(struct Node* r) { if(!r) return; printf("%d ", r->data); preorder(r->left); preorder(r->right); }
void postorder(struct Node* r) { if(!r) return; postorder(r->left); postorder(r->right); printf("%d ", r->data); }
int main() { struct Node* root = create(1); root->left = create(2); root->right = create(3); root->left->left = create(4); printf("\n===== TREE TRAVERSALS =====\n"); printf("Inorder: "); inorder(root); printf("\nPreorder: "); preorder(root); printf("\nPostorder: "); postorder(root); printf("\n"); return 0; }
