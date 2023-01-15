/**
 * @author Rus Ionel
 * @group 30224
 *
 *  Analiza și Compararea Metodelor Directe de Sortare
 *
 * 1. BubbleSort
 * 1.1 In cazul mediu static avem complexitate: O(n^2), deoarece se fac n/2 pasi si la fiecare pas se fac O(n) comparatii. Se ia pe rand de la primul element, se fac comparatii cu vecinul i+1 si la fiecare pas, un element ajunge la pozitia lui, deci n-1 elemente o sa fie sortate.
 * 1.2 In cazul cel mai favorabil avem complexitate: O(n), deoarece chiar daca vectorul e sortat, comparatiile o sa se faca.
 * 1.3 In cazul cel mai defavorabil avem complexitate: O(n^2), deoarece se fac n pasi si la fiecare pas O(n) comparatii.
 * 1.4 Dezavantaj: pentru o cantitate mare de date, vectorul sorteaza foarte lent.
 * 
 * 2. InsertionSort
 * 2.1 In cazul mediu static avem complexitate: O(n^2), deoarece fiecare element incepand cu al doilea o sa fie comparat cu elementele din stanga pana o sa fie inserat la locul lui.
 * 2.2 In cazul cel mai favorabil avem complexitate: O(n), deoarece in bucla interioara se face o singura comparatie si nicio atribuire. Daca avem n elemente o sa avem n-1 pasi, deoarece incepem cu al doilea element, deci rezulta O(n-1)=O(n).
 * 2.3 In cazul cel mai defavorabil avem complexitate: O(n^2), deoarece vectorul este sortat descrescator si la fiecare pas, toate elementele subvectorului o sa fie shiftate la dreapta, deci de fiecare data elementul pe care se face comparatia o sa fie la inceput si toate elementele din stanga lui o sa fie sortate.
 * 2.4 Dezavantaj: pentru o cantitate mare de date, vectorul sorteaza foarte lent.
 * 
 * 3. SelectionSort
 * 3.1 In cazul mediu static avem complexitate: O(n^2), deoarece se cauta mereu minimul, initial in tot vectorul, deci n-1 iteratii, dupa incepand cu al doilea si tot asa, deci rezulta n(n+1)/2 iteratii. De asemenea avem doua bucle care depind una de alta.
 * 3.2 In cazul cel mai favorabil avem complexitate: O(n^2), idem ^^.
 * 3.3 In cazul cel mai defavorabil avem complexitate: O(n^2), idem ^^.
 * 3.4 Dezavantaj: este un algoritm instabil, deoarece nu stim exact ce comparatii a facut in trecut
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"
#define MAX_SIZE 1000
#define NR_TESTS 5
#define STEP_SIZE 100
Profiler profiler("Average_Case");

void printArray(int V[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", V[i]);
	}
	printf("\n");
}

void BubbleSort(int V[], int n) {
	Operation bubbleComp = profiler.createOperation("1 - bubbleComp", n);
	Operation bubbleAssign = profiler.createOperation("2 - bubbleAssign", n);
	for (int i = 0; i < n - 1; i++) {
		int sortat = 1;
		for (int j = 0; j < n - i - 1; j++)
		{
			bubbleComp.count();
			if (V[j] > V[j + 1])
			{
				int temp = V[j];
				V[j] = V[j + 1];
				V[j + 1] = temp;
				bubbleAssign.count(3);
				sortat = 0;
			}
		}
		if (sortat == 1)
			break;
	}
}

void InsertionSort(int V[], int n) {
	Operation insertionComp = profiler.createOperation("1 - insertionComp", n);
	Operation insertionAssign = profiler.createOperation("2 - insertionAssign", n);
	for (int i = 1; i <n; i++) {
		int aux = V[i];
		insertionAssign.count();
		int j = i - 1;
		while (j >= 0 and V[j] > aux) {
			insertionComp.count();
			V[j + 1] = V[j];
			insertionAssign.count();
			j--;
		}
		V[j + 1] = aux;
		insertionAssign.count();
	}
}

void SelectionSort(int V[], int n) {
	Operation selectionComp = profiler.createOperation("1 - selectionComp", n);
	Operation selectionAssign = profiler.createOperation("2 - selectionAssign", n);
	for (int i = 0; i < n - 1; i++) {
		int iMin = i;
		for (int j = i + 1; j < n; j++) {
			selectionComp.count();
			if (V[iMin] > V[j]) {
				iMin = j;
			}
		}
		if (iMin != i) {
			int temp = V[i];
			V[i] = V[iMin];
			V[iMin] = temp;
			selectionAssign.count(3);
		}
	}
}

void demo_BubbleSort(int V[], int n) {
	printf("1 - BubbleSort: \n1.1 Unsorted: ");
	printArray(V, n);
	BubbleSort(V, n);
	printf("1.2 Sorted: ");
	printArray(V, n);
}

void demo_InsertionSort(int V[], int n) {
	printf("2 - InsertionSort: \n2.1 Unsorted: ");
	printArray(V, n);
	InsertionSort(V, n);
	printf("2.2 Sorted: ");
	printArray(V, n);
}

void demo_SelectionSort(int V[], int n) {
	printf("3 - SelectionSort: \n3.1 Unsorted: ");
	printArray(V, n);
	SelectionSort(V, n);
	printf("3.2 Sorted: ");
	printArray(V, n);
}

void demo_AverageCase() {
	int avgArray[] = { 1, 5, 2, 3, 7, 4 };
	int const navgArray = sizeof(avgArray) / sizeof(avgArray[0]);
	int copy1avgArray[navgArray];
	CopyArray(copy1avgArray, avgArray, navgArray);
	int copy2avgArray[navgArray];
	CopyArray(copy2avgArray, avgArray, navgArray);
	demo_BubbleSort(avgArray, navgArray);
	demo_InsertionSort(copy1avgArray, navgArray);
	demo_SelectionSort(copy2avgArray, navgArray);
}

void demo_BestCase() {
	int avgArray[] = { 1, 2, 3, 4, 5, 7};
	int const navgArray = sizeof(avgArray) / sizeof(avgArray[0]);
	int copy1avgArray[navgArray];
	CopyArray(copy1avgArray, avgArray, navgArray);
	int copy2avgArray[navgArray];
	CopyArray(copy2avgArray, avgArray, navgArray);
	demo_BubbleSort(avgArray, navgArray);
	demo_InsertionSort(copy1avgArray, navgArray);
	demo_SelectionSort(copy2avgArray, navgArray);
}

void demo_WorstCase() {
	int avgArray[] = { 7, 5, 4, 3, 2, 1};
	int const navgArray = sizeof(avgArray) / sizeof(avgArray[0]);
	int copy1avgArray[navgArray];
	CopyArray(copy1avgArray, avgArray, navgArray);
	int copy2avgArray[navgArray];
	CopyArray(copy2avgArray, avgArray, navgArray);
	demo_BubbleSort(avgArray, navgArray);
	demo_InsertionSort(copy1avgArray, navgArray);
	demo_SelectionSort(copy2avgArray, navgArray);
}
void demo() {
	printf("Average Case:\n\n");
	demo_AverageCase();
	printf("\nBest Case:\n\n");
	demo_BestCase();
	printf("\nWorst Case:\n\n");
	demo_WorstCase();
}
void perf(int order) {
	int V[MAX_SIZE];
	int copyV1[MAX_SIZE];
	int copyV2[MAX_SIZE];
	for (int i = STEP_SIZE; i <= MAX_SIZE; i += STEP_SIZE) {
		for (int j = 1; j <= NR_TESTS; j++) {
			FillRandomArray(V, i, 10, 50000, false, order);
			CopyArray(copyV1, V, i);
			CopyArray(copyV2, copyV1, i);
			BubbleSort(V, i);
			InsertionSort(copyV1, i);
			SelectionSort(copyV2, i);
		}
	}
	profiler.divideValues("1 - bubbleComp", NR_TESTS);
	profiler.divideValues("2 - bubbleAssign", NR_TESTS);
	profiler.addSeries("3 - bubbleCombined", "1 - bubbleComp", "2 - bubbleAssign");
	profiler.divideValues("1 - insertionComp", NR_TESTS);
	profiler.divideValues("2 - insertionAssign", NR_TESTS);
	profiler.addSeries("3 - insertionCombined", "1 - insertionComp", "2 - insertionAssign");
	profiler.divideValues("1 - selectionComp", NR_TESTS);
	profiler.divideValues("2 - selectionAssign", NR_TESTS);
	profiler.addSeries("3 - selectionCombined", "1 - selectionComp", "2 - selectionAssign");
	profiler.createGroup("1 - Comparisons", "1 - bubbleComp", "1 - insertionComp", "1 - selectionComp");
	profiler.createGroup("2 - Assignements", "2 - bubbleAssign", "2 - insertionAssign", "2 - selectionAssign");
	profiler.createGroup("3 - Combined", "3 - bubbleCombined", "3 - insertionCombined", "3 - selectionCombined");
}

void perf_all() {
	perf(UNSORTED);
	profiler.reset("Best_Case");
	perf(ASCENDING);
	profiler.reset("Worst_Case");
	perf(DESCENDING);
	profiler.showReport();
}

int main() {
	//demo();
	perf_all();
}