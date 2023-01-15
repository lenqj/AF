/**
 * @author Rus Ionel
 * @group 30224
 *
 *  Interclasarea eficientă a k siruri ordonate
 *
 * 1. mergekLists
 * Din grafice rezulta faptul ca odata cu cresterea numarului de liste pentru acelasi numar de elemente suma atribuirilor si comparatiilor creste considerabil fapt rezultat din refacerea operatiei de heapify de fiecare data cand se extrage un element.
 * Acest algoritm face minheap pe capul de liste din lista de liste dupa care se extrage minimul fiind in prima lista dupa care se face un heapify pentru a aduce de fiecare data minimul in prima lista. 
 * In momentul in care prima lista este goala, atunci se vor interschimba prima si ultima lista si marimea listei de liste va scadea cu 1.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)
#define PARENT(i) (i/2)
#define MAX_SIZEn 10000
#define STEP_SIZEn 100
#define STEP_SIZEk 10
#define MAX_SIZEk 500

Profiler profiler("profiler");

typedef struct node{
    int key;
    struct node* next;
}NodeT;

void printList(NodeT* root) {
	if (root == NULL) {
		printf("Lista este goala.\n");
	}
	while (root != NULL) {
		printf("%5d  ", root->key);
		root = root->next;
	}
	printf("\n");
}

void printkLists(NodeT** root, int k) {
	if (*root == NULL) {
		printf("Nu exista liste de afisat.\n");
	}
	for (int i = 0; i < k; i++) {
		printf("#%d - ", i + 1);
		printList(root[i]);
	}
}

NodeT* newList(int key) {
	NodeT* aux = (NodeT*)calloc(1, sizeof(NodeT));
	aux->key = key;
	aux->next = NULL;
	return aux;
}

void insertLast(NodeT** root, int key) {
	NodeT* aux = newList(key);
	if (*(root) == NULL) {
		*(root) = aux;
	}
	else {
		NodeT* aux2 = *root;
		while (aux2->next != NULL) {
			aux2 = aux2->next;
		}
		aux2->next=aux; 
	}
}

int deleteFirst(NodeT** root) {
	if (*root == NULL) {
		return NULL;
	}
	else{
		NodeT* aux = *root;
		*root = aux->next;
		return aux->key;
	}
}

NodeT** generatekLists(int n, int k, int min, int max) {
	if (k <= 0) {
		printf("Trebuie sa avem cel putin o lista.\n");
		return NULL;
	}
	if (n <= 0) {
		printf("Trebuie sa avem cel putin un element.\n");
		return NULL;
	}
	if (n < k) {
		printf("Trebuie sa avem cel putin k elemente pentru a forma k liste.\n");
		return NULL;
	}
	if (min < 10 || max < 10) {
		printf("Minimul/Maximul trebuie sa fie mai mare de 10.\n");
		return NULL;
	}
	if (min > 50000 || max > 50000) {
		printf("Minimul trebuie sa fie mai mic de 50000.\n");
		return NULL;
	}
	if (min == max) {
		printf("Minimul si maximul nu pot fi egale.\n");
		return NULL;
	}
	NodeT** root = (NodeT**)calloc(k, sizeof(NodeT*));
	int const size = n / k;
	int* V = (int *)calloc(size, sizeof(int));
	for (int i = 0; i < k; i++) {
		FillRandomArray(V, size+n%k, min, max, false, 1);
		for (int j = 0; j < size; j++) {
			insertLast(&root[i], V[j]);
		}
	}
	for (int l = 0; l < n % k; l++) {
		insertLast(&root[l], V[size + l]);
	}
	return root;
}

void heapify_bottomUp(NodeT** V, int n, int i, Operation heapify_bottomUpComp, Operation heapify_bottomUpAssign) {
	int largest = i;
	if (LEFT(i) < n) {
		heapify_bottomUpComp.count();
		if (V[LEFT(i)]->key < V[largest]->key) {
			largest = LEFT(i);
		}
	}
	if (RIGHT(i) < n) {
		heapify_bottomUpComp.count();
		if (V[RIGHT(i)]->key < V[largest]->key) {
			largest = RIGHT(i);
		}
	}
	if (largest != i) {
		heapify_bottomUpAssign.count(3);
		NodeT* temp = V[i];
		V[i] = V[largest];
		V[largest] = temp;
		heapify_bottomUp(V, n, largest, heapify_bottomUpComp, heapify_bottomUpAssign);
	}
}

void minHeap_bottomUp(NodeT** V, int n, Operation minHeap_bottomUpComp, Operation minHeap_bottomUpAssign) {
	for (int i = n/2 - 1; i >= 0; i--) {
		heapify_bottomUp(V, n, i, minHeap_bottomUpComp, minHeap_bottomUpAssign);
	}
}

void mergekLists(int n, int k, int size, int demo, int min, int max) {
	Operation mergekListsComp = profiler.createOperation("1 - mergekListsComp", size);
	Operation mergekListsAssign = profiler.createOperation("2 - mergekListsAssign", size);
	NodeT** Lists = generatekLists(n, k, min, max);
	if (demo == 1) {
		printf("Before minHeap_bottomUp:\n");
		printkLists(Lists, k);
	}
	minHeap_bottomUp(Lists, k, mergekListsComp, mergekListsAssign);
	if (demo == 1) {
		printf("After minHeap_bottomUp:\n");
		printkLists(Lists, k);
	}
	NodeT* v = NULL;
	int i = 0;
	while(k>0){
		insertLast(&v, deleteFirst(&Lists[0]));
		mergekListsComp.count();
		if (Lists[0] == NULL) {
			mergekListsAssign.count(3);
			NodeT* temp = Lists[0];
			Lists[0] = Lists[k-1];
			Lists[k-1] = temp;
			k--;
		}
		heapify_bottomUp(Lists, k, 0, mergekListsComp, mergekListsAssign);
	}
	if (demo == 1) {
		printf("Sorted List:\n");
		printList(v);
	}
}

void perfn(int k) {
	for (int i = STEP_SIZEn; i <= MAX_SIZEn; i += STEP_SIZEn) {
		mergekLists(i, k, i, 0, 10, 50000);
	}
	profiler.addSeries("3 - mergekListsCombined", "1 - mergekListsComp", "2 - mergekListsAssign");
}

void perf_alln() {
	int V[] = { 5, 10, 100 };
	int const n = sizeof(V) / sizeof(V[0]);
	for (int i = 0; i < n; i++) {
		char name[15];
		snprintf(name, 15, "merge%dLists", V[i]);
		profiler.reset(name);
		perfn(V[i]);
	}
	profiler.showReport();
}

void perfk() {
	for (int i = STEP_SIZEk; i <= MAX_SIZEk; i += STEP_SIZEk) {
		mergekLists(MAX_SIZEn, i, i, 0, 10, 50000);
	}
	profiler.addSeries("3 - mergekListsCombined", "1 - mergekListsComp", "2 - mergekListsAssign");
}

void perf_allk() {
	profiler.reset("mergekLists");
	perfk();
	profiler.showReport();
}

void demo_mergekLists() {
	int n, k, min, max;
	printf("Numarul de elemente?\n");
	scanf_s("%d", &n);
	printf("Numarul de liste?\n");
	scanf_s("%d", &k);
	printf("minRandom?\n");
	scanf_s("%d", &min);
	printf("maxRandom?\n");
	scanf_s("%d", &max);
	mergekLists(n, k, n, 1, min, max);
}

int main() {
	//perf_alln();
	//perf_allk();
	demo_mergekLists();
}
	