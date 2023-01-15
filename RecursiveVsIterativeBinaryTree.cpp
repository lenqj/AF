/**
 * @author Rus Ionel
 * @group 30224
 *
 *  Parcurgere iterativă vs recursivă arbore binar. Hibridizare quicksort. Analiza comparativă a timpului de execuție.
 * 
 * Am facut cateva teste si am observat optimul prag fiind 26, avand cel mai mic numar de operatii atat pentru cazurile mici, cat si pentru cele mari.
 * Am creat arborele cu functia din laboratorul 7, folosind aceeasi metoda, dar vectorul de data asta este nesortat, deci rezulta un arbore binar cu chei aleatoare.
 * Pentru arbore am inceput din root si dupa am mers pe stanga sau dreapta repetand aceleasi operatii. Se cauta predecesorul pentru nodul curent, cel mai din stanga fiind primul si dupa daca dreapta predecesorului este null atunci se modifica root-ul.
 * 
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"
#define MAX_SIZE 10000
#define NR_TESTS 100
#define STEP_SIZE 100
Profiler profiler("Average_Case");

typedef struct NodeT {
	int key;
	int size;
	struct NodeT* left;
	struct NodeT* right;
}NodeT;

NodeT* createnewNode(int val) {
	NodeT* p = (NodeT*)malloc(sizeof(NodeT));
	p->key = val;
	p->right = p->left = NULL;
	return p;
}

void printArray(int V[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", V[i]);
	}
	printf("\n");
}

void InsertionSort(int V[], int l, int r, Operation insertionTotal) {
	for (int i = l + 1; i <= r; i++) {
		int aux = V[i];
		insertionTotal.count();
		int j = i - 1;
		while (j >= l and V[j] > aux) {
			insertionTotal.count();
			V[j + 1] = V[j];
			insertionTotal.count();
			j--;
		}
		V[j + 1] = aux;
		insertionTotal.count();
	}
}

int partition_quickSort(int V[], int i, int j, Operation partition_quickSortTotal) {
	partition_quickSortTotal.count();
	int aux = V[j];
	int m = i - 1;
	for (int n = i; n < j; n++) {
		partition_quickSortTotal.count();
		if (V[n] < aux) {
			m++;
			partition_quickSortTotal.count(3);
			int temp = V[m];
			V[m] = V[n];
			V[n] = temp;
		}
	}
	partition_quickSortTotal.count(3);
	int temp = V[m + 1];
	V[m + 1] = V[j];
	V[j] = temp;
	return m + 1;
}

void quickSort(int V[], int i, int j, int n, Operation quickSortTotal) {
	if (i < j) {
		int k = partition_quickSort(V, i, j, quickSortTotal);
		quickSort(V, i, k - 1, n, quickSortTotal);
		quickSort(V, k + 1, j, n, quickSortTotal);
	}
}
void quickSortHybrid(int V[], int i, int j, int n, int prag) {
	Operation quickSortHybridTotal = profiler.createOperation("quickSortHybridTotal", n);
	if (i < j) {
		if (j - i < prag) {
			InsertionSort(V, i, j, quickSortHybridTotal);
		}
		else
		{
			int k = partition_quickSort(V, i, j, quickSortHybridTotal);
			quickSortHybrid(V, i, k - 1, n, prag);
			quickSortHybrid(V, k + 1, j, n, prag);
		}
	}
}
void call_quickSort(int V[], int i, int j, int n) {
	Operation quickSortTotal = profiler.createOperation("quickSortTotal", n);
	quickSort(V, i, j, n, quickSortTotal);
}

void perf(int order, int prag) {
	int V[MAX_SIZE];
	int copyV1[MAX_SIZE];
	for (int i = STEP_SIZE; i <= MAX_SIZE; i += STEP_SIZE) {
		for (int j = 1; j <= NR_TESTS; j++) {
			FillRandomArray(V, i, 10, 50000, false, order);
			CopyArray(copyV1, V, i);
			quickSortHybrid(V, 0, i - 1, i, prag);
			call_quickSort(copyV1, 0, i - 1, i);
		}
	}
	profiler.divideValues("quickSortHybridTotal", NR_TESTS);
	profiler.divideValues("quickSortTotal", NR_TESTS);
	profiler.createGroup("Combined", "quickSortHybridTotal", "quickSortTotal");
}

void perf_all() {
	/*int v[] = { 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30 };
	for (int i = 0; i < sizeof(v) / sizeof(v[0]); i++) {
		char name[8];
		snprintf(name, 8, "prag=%d", v[i]);
		profiler.reset(name);
		perf(UNSORTED, v[i]);
	}*/
	profiler.reset("oprag=26");
	perf(UNSORTED, 26);
	profiler.showReport();
}

void demo() {
	int V[20];
	FillRandomArray(V, 20, 10, 50, false, UNSORTED);
	printf("Before quickSortHybrid\n");
	printArray(V, 20);
	quickSortHybrid(V, 0, 20 - 1, 20, 26);
	printf("After quickSortHybrid\n");
	printArray(V, 20);
}

NodeT* buildTree(int left, int right, int v[]) {
	if (left > right) {
		return NULL;
	}
	int mid = (left + right + 1) / 2;
	NodeT* newNode = createnewNode(v[mid]);
	newNode->left = buildTree(left, mid - 1, v);
	newNode->right = buildTree(mid + 1, right, v);
	return newNode;
}

void preOrderIterative(NodeT* root, int n) {
	Operation preOrderIterativeTotal = profiler.createOperation("preOrderIterativeTotal", n);
	if (!root) {
		return;
	}
	while (root) {
		if (root->left) {
			NodeT* p = root->left;
			while (p->right && p->right != root) {
					p = p->right;
			}
			preOrderIterativeTotal.count();
			if (!p->right) {
				p->right = root;
				//printf("%d ", root->key);
				root = root->left;
			}
			else{
				p->right = NULL;
				root = root->right;
			}
		}
		else{
			//printf("%d ", root->key);
			preOrderIterativeTotal.count();
			root = root->right;
		}
	}
}
void preOrderRecursive(NodeT* root, int n, Operation preOrderRecursiveTotal) {
	if (root) {
		preOrderRecursiveTotal.count();
		//printf("%d ", root->key);
		preOrderRecursive(root->left, n, preOrderRecursiveTotal);
		preOrderRecursive(root->right, n, preOrderRecursiveTotal);
	}
}
void call_preOrderRecursive(NodeT* root, int n) {
	Operation preOrderRecursiveTotal = profiler.createOperation("preOrderRecursiveTotal", n);
	preOrderRecursive(root, n, preOrderRecursiveTotal);
}
void demo_tree() {
	profiler.reset("demoTree");
	int v[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	int n = sizeof(v) / sizeof(v[0]);
	printArray(v, n);
	NodeT* tree = buildTree(0, n - 1, v);
	call_preOrderRecursive(tree, n);
	printf("\n");
	preOrderIterative(tree, n);
	profiler.showReport();
}

void perf_tree(int order) {
	int V[MAX_SIZE];
	for (int i = STEP_SIZE; i <= MAX_SIZE; i += STEP_SIZE) {
			FillRandomArray(V, i, 10, 50000, false, order);
			NodeT* tree = buildTree(0, i - 1, V);
			call_preOrderRecursive(tree, i);
			preOrderIterative(tree, i);
	}
	profiler.createGroup("Combined", "preOrderRecursiveTotal", "preOrderIterativeTotal");
}
void perf_all_tree() {
	profiler.reset("perfTree");
	perf_tree(UNSORTED);
	profiler.showReport();
}
int main() {
	//demo();
	demo_tree();
	//perf_all_tree();
	//perf_all();

}