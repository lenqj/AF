/**
 * @author Rus Ionel
 * @group 30224
 *
 * Căutarea în tabele de dispersie 
 * Adresare deschisa, verificare pătratică
 * 
 * 
 * 1. hashTable
 * 1.1 adaugarea, stergerea si cautarea in hashTable sunt O(1) in cazul in care nu sunt coliziuni, iar in cazul in care sunt coliziuni O(j), in cel mai rau caz O(n).
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 10007
#define DEMO_SIZE 20
#define C1 2
#define C2 3
#include "Profiler.h"
typedef struct hTable
{
    int val;
} hTable;
typedef struct ieff {
    int index;
    int effort;
}ieff;
int hFunction(int key, int hSize)
{
    return key % hSize;
}
int h1Function(int key, int j, int hSize ) {
    return (hFunction(key, hSize) + C1 * j + C2 * j * j) % hSize;
}

int tableSize(hTable T[], int hSize) {
    int size = 0;
    for (int i = 0; i < hSize; i++) {
        if (T[i].val != -1) {
            size++;
        }
    }
    return size;
}

ieff* quadraticHashing(hTable T[], int v[], int n, int a, int hSize) {
    ieff* ret = (ieff*)calloc(n, sizeof(ieff));
    for (int i = 0; i < n; i++) {
        if ((tableSize(T, hSize) * 100) / hSize < a) {
            int h = hFunction(v[i], hSize);
            if (T[h].val == -1) {
                T[h].val = v[i];
                ret[i].index = h;
                ret[i].effort = 1;
            }
            else {
                for (int j = 0; j < hSize; j++) {
                    int h1 = h1Function(v[i], j, hSize);
                    if (T[h1].val == -1) {
                        T[h1].val = v[i];
                        ret[i].index = h1;
                        ret[i].effort = j;
                        break;
                    }
                    else {
                        ret[i].index = -1;
                        ret[i].effort = j;
                    }
                }
            }
        }
        else{
            ret[i].index = -1;
            ret[i].effort = hSize-1;
        }
    }
    return ret;
}

ieff* searchKeys(hTable T[], int v[], int n, int hSize) {
    ieff* ret = (ieff*)calloc(n, sizeof(ieff));
    for (int i = 0; i < n; i++) {
            int h = hFunction(v[i], hSize);
            if (T[h].val == v[i]) {
                ret[i].index = h;
                ret[i].effort = 1;
            }
            else {
                for (int j = 1; j < hSize; j++) {
                    int h1 = h1Function(v[i], j, hSize);
                    if (T[h1].val == v[i]) {
                        ret[i].index = h1;
                        ret[i].effort = j;
                        break;
                    }
                    else {
                        ret[i].index = -1;
                        ret[i].effort = j;
                    }
                }
            }
    }
    return ret;
}

ieff* deleteKeys(hTable T[], int v[], int n, int a, int hSize) {
    ieff* ret = (ieff*)calloc(n, sizeof(ieff));
    for (int i = 0; i < n; i++) {
        if ((tableSize(T, hSize) * 100) / hSize > a) {
            int h = hFunction(v[i], hSize);
            if (T[h].val == v[i]) {
                T[h].val = -1;
                ret[i].index = h;
                ret[i].effort = 1;
            }
            else {
                for (int j = 1; j < hSize; j++) {
                    int h1 = h1Function(v[i], j, hSize);
                    if (T[h1].val == v[i]) {
                        T[h1].val = -1;
                        ret[i].index = h1;
                        ret[i].effort = j;
                        break;
                    }
                    else {
                        ret[i].index = -1;
                        ret[i].effort = j;
                    }
                }
            }
        }
        else{
            ret[i].index = -1;
            ret[i].effort = hSize-1;
        }
    }
    return ret;
}

void printArray(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%5d ", v[i]);
    }
    printf("\n");
}

void printIEFF(int v1[], ieff v[], int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] - index: %d, effort: %d\n", v1[i], v[i].index, v[i].effort);
    }
    printf("\n");
}

void printhTable(hTable T[], int hSize) {
    for (int i = 0; i < hSize; i++) {
        printf("T[%1d] = %5d\n", i, T[i].val);
    }
    printf("a = %d%%\n", (tableSize(T, hSize)*100)/hSize);
    printf("\n");
}

void initializehTable(hTable T[], int hSize) {
    for (int i = 0; i < hSize; i++) {
        T[i].val = -1;
    }
}
int* initializeRandomArray(int* v, int n, int hSize) {
    int* ret = (int*)calloc(n, sizeof(int));
    FillRandomArray(ret, n / 2, 10, 50000, true, 0);
    int j = 0;
    int *aux = (int*)calloc(n/2, sizeof(int));
    FillRandomArray(aux, n / 2, 10, 50000, true, 0);
    for (int i = n / 2; i < n; i++) {
        ret[i] = v[aux[j++] % hSize];
    }
    return ret;
}
int* countEffort(ieff v[], int hSize) {
    int* count = (int*)calloc(2, sizeof(int));
    for (int i = 0; i < hSize; i++) {
        if (v[i].index != -1) {
            count[0] += v[i].effort;
        }
        else {
            count[1] += v[i].effort;
        }
    }
    return count;
}
int* maxEffort(ieff v[], int hSize) {
    int* max = (int*)calloc(2, sizeof(int));
    max[0] = -1000;
    max[1] = -1000;
    for (int i = 0; i < hSize; i++) {
        if (v[i].index != -1) {
            if (v[i].effort > max[0]) {
                max[0] = v[i].effort;
            }
        }
        else {
            if (v[i].effort > max[1]) {
                max[1] = v[i].effort;
            }
        }
    }
    return max;
}
void demo() {
    printf("                                                     DEMO.....\n");
    hTable T[DEMO_SIZE];
    initializehTable(T, DEMO_SIZE);
    int a = 90;
    int* v = (int*)calloc(DEMO_SIZE, sizeof(int));
    FillRandomArray(v, DEMO_SIZE, 10, 50000, true, 0);
    printArray(v, DEMO_SIZE);
    ieff* insert= quadraticHashing(T, v, DEMO_SIZE, a, DEMO_SIZE);
    printIEFF(v, insert, DEMO_SIZE);
    printhTable(T, DEMO_SIZE);
    int* searcharr = initializeRandomArray(v, DEMO_SIZE, DEMO_SIZE);
    ieff* search = searchKeys(T, searcharr, DEMO_SIZE, DEMO_SIZE);
    printArray(searcharr, DEMO_SIZE);
    printIEFF(searcharr, search, DEMO_SIZE);
    int a2 = 80;
    ieff* deleted = deleteKeys(T, searcharr, DEMO_SIZE, a2, DEMO_SIZE);
    printArray(searcharr, DEMO_SIZE);
    printIEFF(searcharr, search, DEMO_SIZE);
    printhTable(T, DEMO_SIZE);
    int *count = countEffort(search, DEMO_SIZE);
    int* max = maxEffort(search, DEMO_SIZE);
    printf(" | Factor de umplere: | Efort mediu gasite: | Efort mediu negasite: | Efort maxim gasite: | Efort maxim negasite: | \n");
    printf(" | 0.%-16d | %-19.2f | %-21.2f | %-19d | %-21d | \n", tableSize(T, DEMO_SIZE) * 100 / DEMO_SIZE, count[0] * 1.0 / (DEMO_SIZE/2) * 1.0, count[1] * 1.0 / (DEMO_SIZE/2) * 1.0, max[0], max[1]);
}
void perf() {
    printf("\n\n                                                     PERF.....\n\n");
    hTable T[M];
    initializehTable(T, M);
    int a[] = {80, 85, 90, 95, 99};
    int m = 3000;
    int* v = (int*)calloc(M, sizeof(int));
    int* count = NULL;
    int* max = NULL;
    printf(" | Factor de umplere: | Efort mediu gasite: | Efort mediu negasite: | Efort maxim gasite: | Efort maxim negasite: | \n");
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        FillRandomArray(v, M, 10, 50000, true, 0);
        ieff* insert = quadraticHashing(T, v, M, a[i], M);
        //printhTable(T, M);
        int* searcharr = initializeRandomArray(v, m, M);
        ieff* search = searchKeys(T, searcharr, m, M);
        count = countEffort(search, m);
        max = maxEffort(search, m);
        printf(" | 0.%-16d | %-19.2f | %-21.2f | %-19d | %-21d | \n", tableSize(T, M) * 100 / M, count[0] * 1.0 / 1500 * 1.0, count[1] * 1.0 / 1500 * 1.0, max[0], max[1]);
    }    
    FillRandomArray(v, m, 10, 50000, true, 0);
    int* deletearr = initializeRandomArray(v, M, M);
    ieff* delete1 = deleteKeys(T, deletearr, M, 80, M);
    count = countEffort(delete1, M);
    max = maxEffort(delete1, M);
    printf(" | 0.%-16d | %-19.2f | %-21.2f | %-19d | %-21d | \n", tableSize(T, M)*100/M, count[0] * 1.0 / 1500 * 1.0, count[1] * 1.0 / 1500 * 1.0, max[0], max[1]);

}

int main()
{
    demo();
    perf();
    return 0;
}
