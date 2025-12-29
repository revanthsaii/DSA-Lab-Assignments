#include <stdio.h>
#include <stdlib.h>
struct Node { int data; struct Node *left, *right; };
struct Node* newNode(int x) { struct Node* n = malloc(sizeof(struct Node)); n->data=x; n->left=n->right=NULL; return n; }
struct Node* insert(struct Node* r, int x) { if(!r) return newNode(x); if(x<r->data) r->left=insert(r->left,x); else r->right=insert(r->right,x); return r; }
void inorder(struct Node* r) { if(!r) return; inorder(r->left); printf("%d ", r->data); inorder(r->right); }
int main() { struct Node* root=NULL; int arr[]={50,30,70,20,40,60,80}; int n=7; printf("\n===== BINARY SEARCH TREE =====\n"); for(int i=0;i<n;i++) root=insert(root,arr[i]); printf("Inorder: "); inorder(root); printf("\n"); return 0; }
