/**
 * @author Rus Ionel
 * @group 30224
 *
 *  Analiza și Compararea metodelor avansate de sortare - HeapSort si QuickSort
 *
 * 1. heapSort
 * 1.1 In cazul mediu static avem complexitate: O(n*log(n)), deoarece se parcurge vectorul de la primul element pana la mijloc pentru crearea heap-ului prin aducerea elementului de la frunza catre radacina. Complexitatea pentru heapify este lgn egala cu inaltimea/adancimea heap-ului.
 * 1.2 In cazul cel mai defavorabil avem complexitate: O(n*log(n)), idem, dar este cazul in care fiecare copil trebuie interschimbat cu parintele.
 * 1.3 In cazul cel mai favorabil avem complexitate: O(n*log(n)), idem, dar este cazul in care vectorul este deja sortat si radacina este radacina.
 *
 * 2. quickSort
 * 2.1 In cazul mediu static avem complexitate: O(n*log(n)), deoarece se formeaza doi subvectori, vectorul stang cu elementele mai mici decat pivotul si in vectorul drept elementele mai mari decat pivotul si tot partitioneaza pana se ajunge la vector de un element.
 * 2.2 In cazul cel mai defavorabil avem complexitate: O(n^2), este cazul in care vectorul este sortat descrescator/crescator, pivotul fiind ultimul sau primul element.
 * 2.3 In cazul cel mai favorabil avem complexitate: O(n*log(n)), poate fi considerat acelasi cu average conform graficelor.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"
#define MAX_SIZE 5000
#define NR_TESTS 5
#define STEP_SIZE 100
#define TIME_SIZE 5000
#define TIME_NR_TESTS 1000
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)
#define PARENT(i) (i/2)
Profiler pheapSortandquickSort("heapSortandquickSort_Average_Case");
Profiler pquickSort("quickSort_Average_Case");
Profiler pbubbleSort("BubbleSort_Average_Case");
Profiler pbubbleSortTime("bubbleSortTime");

void printArray(int V[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", V[i]);
	}
	printf("\n");
}

void heapify_bottomUp(int V[], int n, int i, Operation heapify_bottomUpComp, Operation heapify_bottomUpAssign) {
	int largest = i;
	if (LEFT(i) < n) {
		heapify_bottomUpComp.count();
		if (V[LEFT(i)] > V[largest]) {
			largest = LEFT(i);
		}
	}
	if (RIGHT(i) < n) {
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
		heapify_bottomUp(V, n, largest, heapify_bottomUpComp, heapify_bottomUpAssign);
	}
}

void maxHeap_bottomUp(int V[], int n, Operation maxHeap_bottomUpComp, Operation maxHeap_bottomUpAssign) {
	for (int i = n / 2 - 1 ; i >= 0; i--) {
		heapify_bottomUp(V, n, i, maxHeap_bottomUpComp, maxHeap_bottomUpAssign);
	}
}

void heapSort(int V[], int n) {
	Operation heapSortComp = pheapSortandquickSort.createOperation("1 - heapSortComp", n);
	Operation heapSortAssign = pheapSortandquickSort.createOperation("2 - heapSortAssign", n);
	maxHeap_bottomUp(V, n, heapSortComp, heapSortAssign);
	for (int i = n - 1; i >= 0; i--) {
		heapSortAssign.count(3);
		int temp = V[i];
		V[i] = V[0];
		V[0] = temp;
		heapify_bottomUp(V, i, 0, heapSortComp, heapSortAssign);
	}
}

int partition_quickSort(int V[], int i, int j, Operation partition_quickSortComp, Operation partition_quickSortAssign) {
	partition_quickSortAssign.count();
	int aux = V[j];
	int m = i - 1;
	for (int n = i; n < j; n++) {
		partition_quickSortComp.count();
		if (V[n] < aux) {
			m++;
			partition_quickSortAssign.count(3);
			int temp = V[m];
			V[m] = V[n];
			V[n] = temp;
		}
	}
	partition_quickSortAssign.count(3);
	int temp = V[m+1];
	V[m+1] = V[j];
	V[j] = temp;
	return m + 1;
}

void quickSort(int V[], int i, int j, int n, Operation quickSortComp, Operation quickSortAssign) {
	if (i < j) {
		int k = partition_quickSort(V, i, j, quickSortComp, quickSortAssign);
		quickSort(V, i, k - 1, n, quickSortComp, quickSortAssign);
		quickSort(V, k + 1, j, n, quickSortComp, quickSortAssign);
	}
}

void call_quickSort(int V[], int i, int j, int n, int qhb) {
	if (qhb == 0) {
		Operation quickSortComp = pheapSortandquickSort.createOperation("1 - quickSortComp", n);
		Operation quickSortAssign = pheapSortandquickSort.createOperation("2 - quickSortAssign", n);
		quickSort(V, i, j, n, quickSortComp, quickSortAssign);
	}
	else if (qhb == 1) {
		Operation quickSortComp = pquickSort.createOperation("1 - quickSortComp", n);
		Operation quickSortAssign = pquickSort.createOperation("2 - quickSortAssign", n);
		quickSort(V, i, j, n, quickSortComp, quickSortAssign);
	}
}

void iterative_bubbleSort(int V[], int n) {
	Operation iterative_bubbleComp = pbubbleSort.createOperation("1 - iterative_bubbleComp", n);
	Operation iterative_bubbleAssign = pbubbleSort.createOperation("2 - iterative_bubbleAssign", n);
	for (int i = 0; i < n - 1; i++) {
		int sortat = 1;
		for (int j = 0; j < n - i - 1; j++) {
			iterative_bubbleComp.count();
			if (V[j] > V[j + 1])
			{
				int temp = V[j];
				V[j] = V[j + 1];
				V[j + 1] = temp;
				iterative_bubbleAssign.count(3);
				sortat = 0;
			}
		}
		if (sortat == 1)
			break;
	}
}

void recursive_bubbleSort(int V[], int n, Operation recursive_bubbleComp, Operation recursive_bubbleAssign) {
	if (n == 1)
		return;
	int sortat = 0;
	for (int i = 0; i < n - 1; i++) {
		recursive_bubbleComp.count();
		if (V[i] > V[i + 1]) {
			recursive_bubbleAssign.count(3);
			int temp = V[i];
			V[i] = V[i + 1];
			V[i + 1] = temp;
			sortat = 1;
		}
	}
	if (sortat == 0)
		return;
	recursive_bubbleSort(V, n - 1, recursive_bubbleComp, recursive_bubbleAssign);
}

void call_recursive_bubbleSort(int V[], int n) {
	Operation recursive_bubbleComp = pbubbleSort.createOperation("1 - recursive_bubbleComp", n);
	Operation recursive_bubbleAssign = pbubbleSort.createOperation("2 - recursive_bubbleAssign", n);
	recursive_bubbleSort(V, n, recursive_bubbleComp, recursive_bubbleAssign);
}

void perf(int qhb, int order) {
	
	int V[MAX_SIZE];
	for (int i = STEP_SIZE; i <= MAX_SIZE; i += STEP_SIZE) {
		for (int j = 1; j <= NR_TESTS; j++) {
			FillRandomArray(V, i, 10, 50000, false, order);
			if (qhb == 0) {
				int copyV1[MAX_SIZE];
				CopyArray(copyV1, V, i);
				heapSort(V, i);
				call_quickSort(copyV1, 0, i - 1, i, qhb);

			}
			else if (qhb == 1) {
				call_quickSort(V, 0, i - 1, i, qhb);
			}
			else if (qhb == 2) {
				int copyV1[MAX_SIZE];
				CopyArray(copyV1, V, i);
				iterative_bubbleSort(V, i);
				call_recursive_bubbleSort(copyV1, i);
			}
		}
	}
	if (qhb == 0) {
		pheapSortandquickSort.divideValues("1 - heapSortComp", NR_TESTS);
		pheapSortandquickSort.divideValues("2 - heapSortAssign", NR_TESTS);
		pheapSortandquickSort.addSeries("3 - heapSortCombined", "1 - heapSortComp", "2 - heapSortAssign");
		pheapSortandquickSort.divideValues("1 - quickSortComp", NR_TESTS);
		pheapSortandquickSort.divideValues("2 - quickSortAssign", NR_TESTS);
		pheapSortandquickSort.addSeries("3 - quickSortCombined", "1 - quickSortComp", "2 - quickSortAssign");
		pheapSortandquickSort.createGroup("1 - Comparisons", "1 - heapSortComp", "1 - quickSortComp");
		pheapSortandquickSort.createGroup("2 - Assignements", "2 - heapSortAssign", "2 - quickSortAssign");
		pheapSortandquickSort.createGroup("3 - Combined", "3 - heapSortCombined", "3 - quickSortCombined");
	}
	else if (qhb == 1){
		pquickSort.divideValues("1 - quickSortComp", NR_TESTS);
		pquickSort.divideValues("2 - quickSortAssign", NR_TESTS);
		pquickSort.addSeries("3 - quickSortCombined", "1 - quickSortComp", "2 - quickSortAssign");
	}
	else if (qhb == 2) {
		pbubbleSort.divideValues("1 - iterative_bubbleComp", NR_TESTS);
		pbubbleSort.divideValues("2 - iterative_bubbleAssign", NR_TESTS);
		pbubbleSort.addSeries("3 - iterative_bubbleCombined", "1 - iterative_bubbleComp", "2 - iterative_bubbleAssign");
		pbubbleSort.divideValues("1 - recursive_bubbleComp", NR_TESTS);
		pbubbleSort.divideValues("2 - recursive_bubbleAssign", NR_TESTS);
		pbubbleSort.addSeries("3 - recursive_bubbleCombined", "1 - recursive_bubbleComp", "2 - recursive_bubbleAssign");
		pbubbleSort.createGroup("1 - Comparisons", "1 - iterative_bubbleComp", "1 - recursive_bubbleComp");
		pbubbleSort.createGroup("2 - Assignements", "2 - iterative_bubbleAssign", "2 - recursive_bubbleAssign");
		pbubbleSort.createGroup("3 - Combined", "3 - iterative_bubbleCombined", "3 - recursive_bubbleCombined");
		pbubbleSort.createGroup("3 - Combined", "3 - iterative_bubbleCombined", "3 - recursive_bubbleCombined");
	}
}

void perf_all(int qhb) {
	if (qhb == 0) {
		perf(qhb, UNSORTED);
		pheapSortandquickSort.reset("heapSortandquickSort_Worst_Case");
		perf(qhb, DESCENDING);
		pheapSortandquickSort.reset("heapSortandquickSort_Best_Case");
		perf(qhb, ASCENDING);
		pheapSortandquickSort.showReport();
	}
	else if (qhb == 1) {
		perf(qhb, UNSORTED);
		pquickSort.reset("quickSort_Worst_Case");
		perf(qhb, DESCENDING);
		pquickSort.reset("quickSort_Best_Case");
		perf(qhb, ASCENDING);
		pquickSort.showReport();
	}
	else if (qhb == 2) {
		perf(qhb, UNSORTED);
		pbubbleSort.reset("bubbleSort_Worst_Case");
		perf(qhb, DESCENDING);
		pbubbleSort.reset("bubbleSort_Best_Case");
		perf(qhb, ASCENDING);
		pbubbleSort.showReport();
	}
}
void bubbleSortTime() {
	int V[TIME_SIZE];
	int copyV1[TIME_SIZE];
	int copyV2[TIME_SIZE];
	FillRandomArray(V, TIME_SIZE, 10, 50000, false, 0);
	CopyArray(copyV1, V, TIME_SIZE);
	CopyArray(copyV2, V, TIME_SIZE);
	pbubbleSortTime.startTimer("4 - iterative_bubbleTime", TIME_SIZE);
	for (int j = 0; j < TIME_SIZE; j++) {
		iterative_bubbleSort(copyV1, TIME_SIZE);
	}
	pbubbleSortTime.stopTimer("4 - iterative_bubbleTime", TIME_SIZE);

	pbubbleSortTime.startTimer("4 - recursive_bubbleTime", TIME_SIZE);
	for (int j = 0; j < TIME_SIZE; j++) {
		call_recursive_bubbleSort(copyV2, TIME_SIZE);
	}
	pbubbleSortTime.stopTimer("4 - recursive_bubbleTime", TIME_SIZE);
	pbubbleSortTime.createGroup("4 - Time", "4 - iterative_bubbleTime", "4 - recursive_bubbleTime");
	pbubbleSortTime.showReport();
}

void demo_quickSort(int V[], int n) {
	printf("1 - quickSort: \n1.1 Before quickSort: ");
	printArray(V, n);
	call_quickSort(V, 0, n - 1, n, 1);
	printf("1.2 After quickSort: ");
	printArray(V, n);
}

void demo_heapSort(int V[], int n) {
	printf("2 - heapSort: \n2.1 Before heapSort: ");
	printArray(V, n);
	heapSort(V, n);
	printf("2.2 After heapSort: ");
	printArray(V, n);
}

void demo_iterative_bubbleSort(int V[], int n) {
	printf("3 - iterative_bubbleSort: \n3.1 Before iterative_bubbleSort: ");
	printArray(V, n);
	iterative_bubbleSort(V, n);
	printf("3.2 After iterative_bubbleSort: ");
	printArray(V, n);
}

void demo_recursive_bubbleSort(int V[], int n) {
	printf("4 - recursive_bubbleSort: \n4.1 Before recursive_bubbleSort: ");
	printArray(V, n);
	call_recursive_bubbleSort(V, n);
	printf("4.2 After recursive_bubbleSort: ");
	printArray(V, n);
}

void demo_AverageCase() {
	int avgArray[] = { 4, 20, 25, 6, 12, 15, 10, 16 };
	int const navgArray = sizeof(avgArray) / sizeof(avgArray[0]);
	int copy1avgArray[navgArray];
	CopyArray(copy1avgArray, avgArray, navgArray);
	int copy2avgArray[navgArray];
	CopyArray(copy2avgArray, avgArray, navgArray);
	int copy3avgArray[navgArray];
	CopyArray(copy3avgArray, avgArray, navgArray);
	demo_quickSort(avgArray, navgArray);
	demo_heapSort(copy1avgArray, navgArray);
	demo_iterative_bubbleSort(copy2avgArray, navgArray);
	demo_recursive_bubbleSort(copy3avgArray, navgArray);
}

void demo_BestCase() {
	int avgArray[] = { 4, 6, 10, 12, 15, 16, 20, 25 };
	int const navgArray = sizeof(avgArray) / sizeof(avgArray[0]);
	int copy1avgArray[navgArray];
	CopyArray(copy1avgArray, avgArray, navgArray);
	int copy2avgArray[navgArray];
	CopyArray(copy2avgArray, avgArray, navgArray);
	int copy3avgArray[navgArray];
	CopyArray(copy3avgArray, avgArray, navgArray);
	demo_quickSort(avgArray, navgArray);
	demo_heapSort(copy1avgArray, navgArray);
	demo_iterative_bubbleSort(copy2avgArray, navgArray);
	demo_recursive_bubbleSort(copy3avgArray, navgArray);
}

void demo_WorstCase() {
	int avgArray[] = { 25, 20, 16, 15, 12, 10, 6, 4 };
	int const navgArray = sizeof(avgArray) / sizeof(avgArray[0]);
	int copy1avgArray[navgArray];
	CopyArray(copy1avgArray, avgArray, navgArray);
	int copy2avgArray[navgArray];
	CopyArray(copy2avgArray, avgArray, navgArray);
	int copy3avgArray[navgArray];
	CopyArray(copy3avgArray, avgArray, navgArray);
	demo_quickSort(avgArray, navgArray);
	demo_heapSort(copy1avgArray, navgArray);
	demo_iterative_bubbleSort(copy2avgArray, navgArray);
	demo_recursive_bubbleSort(copy3avgArray, navgArray);
}
void demo() {
	printf("Average Case:\n\n\n");
	demo_AverageCase();
	printf("Worst Case:\n\n\n");
	demo_WorstCase();
	printf("Best Case:\n\n");
	demo_BestCase();
}

int main() {
	//demo(); 
	for (int i = 0; i < 3; i++) {
		perf_all(i); // 0 - quickSortandheapSort; 1 - quickSort; 2 - bubbleSort;
	}
	bubbleSortTime();

}