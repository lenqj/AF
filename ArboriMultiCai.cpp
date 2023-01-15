/**
 * @author Rus Ionel
 * @group 30224
 *
 *  Arobri multicai
 *  Transformări între diferite reprezentări
 *
 */

#include <stdlib.h>
#include <stdio.h>

void prettyPrint(int* v, int n, int root, int tabs) {
	for (int i = 0; i < n; i++) {
		if (v[i] == root){
			for (int j = 0; j < tabs; j++) {
				printf("\t");
			}
		printf("%d\n", i + 1);
		prettyPrint(v, n, i + 1, tabs + 1);
		}
	}
}
void perf_prettyPrint() {
	int v[] = { 2, 7, 5, 2, 7, 7, -1, 5, 2 };
	int n = sizeof(v) / sizeof(v[0]);
	prettyPrint(v, n, -1, 0);
}

int main() {
	perf_prettyPrint();
}