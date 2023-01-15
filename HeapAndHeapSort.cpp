/**
 * @author Rus Ionel
 * @group 30224
 *
 *  Analiza și Compararea a doua metode de construire a structurii de date Heap.(bottomUp si topDown)
 *
 * 1. maxHeap_bottomUp
 * 1.1 In cazul mediu static avem complexitate: O(n*log(n)), deoarece se parcurge vectorul de la primul element pana la mijloc pentru crearea heap-ului prin aducerea elementului de la frunza catre radacina. Complexitatea pentru heapify este lgn egala cu inaltimea/adancimea heap-ului.
 * 1.2 In cazul cel mai defavorabil avem complexitate: O(n*log(n)), idem, dar este cazul in care fiecare copil trebuie interschimbat cu parintele. 
 *
 * 2. maxHeap_topDown
 * 2.1 In cazul mediu static avem complexitate: O(n*log(n)), deoarece se parcurge vectorul de la primul element pana la final pentru crearea heap-ului prin aducerea elementului de la radacina catre frunze. Complexitatea pentru heapify este lgn egala cu inaltimea/adancimea heap-ului.
 * 2.2 In cazul cel mai defavorabil avem complexitate: O(n^2), idem, dar este cazul in care radacina tot timpul ajunge sa fie frunza.
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"
#define MAX_SIZE 10000
#define NR_TESTS 5
#define STEP_SIZE 100
#define LEFT(i) (2*i)
#define RIGHT(i) (2*i+1)
#define PARENT(i) (i/2)
Profiler profiler("Average_Case");

void printArray(int V[], int n) {
	for (int i = 1; i < n; i++) {
		printf("%d ", V[i]);
	}
	printf("\n");
}

void heapify_bottomUp(int V[], int i) {
	Operation heapify_bottomUpComp = profiler.createOperation("1 - heapify_bottomUpComp", V[0]);
	Operation heapify_bottomUpAssign = profiler.createOperation("2 - heapify_bottomUpAssign", V[0]);
	int largest = i;
	if (LEFT(i) < V[0]) {
		heapify_bottomUpComp.count();
		if (V[LEFT(i)] > V[largest]) {
			largest = LEFT(i);
		}
	}
	if (RIGHT(i) < V[0]) {
		heapify_bottomUpComp.count();
		if (V[RIGHT(i)] > V[largest]) {
			largest = RIGHT(i);
		}
	}
	if (largest != i) {
		heapify_bottomUpAssign.count(3);
		int temp = V[i];
		V[i] = V[largest];
		V[largest] = temp;
		heapify_bottomUp(V, largest);
	}
}

void maxHeap_bottomUp(int V[]) {
	for (int i = V[0] / 2; i >= 1; i--) {
		heapify_bottomUp(V, i);
	}
}
void heapify_topDown(int V[], int i) {
	Operation heapify_topDownComp = profiler.createOperation("1 - heapify_topDownComp", V[0]);
	Operation heapify_topDownAssign = profiler.createOperation("2 - heapify_topDownAssign", V[0]);

	while (i > 1 && V[PARENT(i)] > V[i]) {
		i = PARENT(i);
		heapify_topDownComp.count();
	}
	while (i > 1 && V[PARENT(i)] < V[i]) {
		heapify_topDownComp.count();
		heapify_topDownAssign.count(3);
		int aux = V[PARENT(i)];
		V[PARENT(i)] = V[i];
		V[i] = aux;
		i = PARENT(i);
	}
}

void maxHeap_topDown(int V[]) {
	for (int i = 2; i < V[0]; i++) {
		heapify_topDown(V, i);
	}
}


void heapSort(int V[]) {
	int aux = V[0];
	maxHeap_bottomUp(V);
	for (int i = V[0] - 1; i >= 2; i--) {
		int temp = V[i];
		V[i] = V[1];
		V[1] = temp;
		V[0]--;
		heapify_bottomUp(V, 1);
	}
	V[0] = aux;
}

void perf(int order) {
	int V[MAX_SIZE];
	int copyV1[MAX_SIZE];
	for (int i = STEP_SIZE; i <= MAX_SIZE; i += STEP_SIZE) {
		for (int j = 1; j <= NR_TESTS; j++) {
			FillRandomArray(V, i, 10, 50000, false, order);
			CopyArray(copyV1, V, i);
			V[0] = copyV1[0] = i;
			maxHeap_bottomUp(V);
			maxHeap_topDown(copyV1);
		}
	}
	profiler.divideValues("1 - heapify_bottomUpComp", NR_TESTS);
	profiler.divideValues("2 - heapify_bottomUpAssign", NR_TESTS);
	profiler.addSeries("3 - bottomUpCombined", "1 - heapify_bottomUpComp", "2 - heapify_bottomUpAssign");
	profiler.divideValues("1 - heapify_topDownComp", NR_TESTS);
	profiler.divideValues("2 - heapify_topDownAssign", NR_TESTS);
	profiler.addSeries("3 - topDownCombined", "1 - heapify_topDownComp", "2 - heapify_topDownAssign");
	profiler.createGroup("1 - Comparisons", "1 - heapify_bottomUpComp", "1 - heapify_topDownComp");
	profiler.createGroup("2 - Assignements", "2 - heapify_bottomUpAssign", "2 - heapify_topDownAssign");
	profiler.createGroup("3 - Combined", "3 - bottomUpCombined", "3 - topDownCombined");
}

void perf_all() {
	perf(UNSORTED);
	profiler.reset("Worst_Case");
	perf(ASCENDING);
	profiler.showReport();
}
void demo_bottomUp(int V[]) {
	printf("1 - bottomUp: \n1.1 Before heapify: ");
	printArray(V, V[0]);
	maxHeap_bottomUp(V);
	printf("1.2 After heapify: ");
	printArray(V, V[0]);
}

void demo_topDown(int V[]) {
	printf("2 - topDown: \n2.1 Before heapify: ");
	printArray(V, V[0]);
	maxHeap_topDown(V);
	printf("2.2 After heapify: ");
	printArray(V, V[0]);
}

void demo_heapSort(int V[]) {
	printf("3 - heapSort: \n3.1 Before heapSort: ");
	printArray(V, V[0]);
	heapSort(V);
	printf("3.2 After heapSort: ");
	printArray(V, V[0]);
}

void demo_AverageCase() {
	int avgArray[] = { 4, 20, 25, 6, 12, 15, 10, 16 };
	int const navgArray = sizeof(avgArray) / sizeof(avgArray[0]);
	int copy1avgArray[navgArray];
	CopyArray(copy1avgArray, avgArray, navgArray);
	int copy2avgArray[navgArray];
	CopyArray(copy2avgArray, avgArray, navgArray);
	avgArray[0] = copy1avgArray[0]  = copy2avgArray[0] = navgArray;
	demo_bottomUp(avgArray);
	demo_topDown(copy1avgArray);
	demo_heapSort(copy2avgArray);
}

void demo_WorstCase() {
	int avgArray[] = { 4, 6, 10, 12, 15, 16, 20, 25 };
	int const navgArray = sizeof(avgArray) / sizeof(avgArray[0]);
	int copy1avgArray[navgArray];
	CopyArray(copy1avgArray, avgArray, navgArray);
	int copy2avgArray[navgArray];
	CopyArray(copy2avgArray, avgArray, navgArray);
	avgArray[0] = copy1avgArray[0] = copy2avgArray[0] = navgArray;
	demo_bottomUp(avgArray);
	demo_topDown(copy1avgArray);
	demo_heapSort(copy2avgArray);
}
void demo() {
	printf("Average Case:\n\n");
	demo_AverageCase();
	printf("\nWorst Case:\n\n");
	demo_WorstCase();
}

int main() {
	//demo();
	perf_all();
}