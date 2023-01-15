/**
 * @author Rus Ionel
 * @group 30224
 *
 *  Statistici dinamice de ordine
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"
#define MAX_SIZE 10000
#define NR_TESTS 5
#define STEP_SIZE 100

typedef struct NodeT {
	int key;
	int size;
	struct NodeT* left;
	struct NodeT* right;
}NodeT;

NodeT* createnewNode(int val) {
	NodeT* p = (NodeT*)malloc(sizeof(NodeT));
	p->key = val;
	p->size = 0;
	p->right = p->left = NULL;
	//p->right->size = p->left->size = 1;
	return p;
}

int noNodes(NodeT* tree)
{
	if (tree == NULL)
		return 0;
	if (tree->left == NULL && tree->right == NULL)
		return 0;
	return 1 + noNodes(tree->left) + noNodes(tree->right);
}
NodeT* buildTree(int left, int right, int v[]) {
	if (left > right) {
		return NULL;
	}
	int mid = (left + right + 1) / 2;
	NodeT* newNode = createnewNode(v[mid]);
	newNode->left = buildTree(left, mid-1, v);
	newNode->right = buildTree(mid+1, right, v);
	newNode->size = 1 + noNodes(newNode->left) + noNodes(newNode->right);
	return newNode;
}
int* createVector(int n) {
	int* v = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		v[i] = i+1;
	}
	return v;
}
void inOrder(NodeT* root)
{
	if (root != NULL)
	{
		inOrder(root->left);
		printf("%d - [%d] \n", root->key, root->size);
		inOrder(root->right);
	}
}
void printTree(NodeT* root, int space){
	if (root == NULL)
		return;
	printTree(root->right, space + 1);
	printf("\n");
	for (int i = 0; i < space; i++) {
		printf("\t");
	}
	printf("%d", root->key);
	printf("\n");
	printTree(root->left, space + 1);
}
NodeT* osSelect(NodeT* root, int i) {
	int r = root->left->size + 1;
	if (i == r) {
		return root;
	}
	else if (i < r) {
		return osSelect(root->left, i);
	}
	else {
		return osSelect(root->right, i - r);
	}
}

void demo() {
	//int v[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	int* v = createVector(11);
	int n = sizeof(v) / sizeof(v[0]);
	for (int i = 0; i < 11; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
	NodeT* tree = buildTree(0, 10, v);
	inOrder(tree);
	printf("\n");
	printTree(tree, 0);
	NodeT* search = osSelect(tree, 2);
	printf("%d ", search->key);
}
int main() {
	demo();
}