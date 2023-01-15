/**
 * @author Rus Ionel
 * @group 30224
 *
 *  Mulțimi disjuncte
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct disJointSet {
	int key;
	int rank;
	struct disJointSet* p;
}disJointSet;

disJointSet* makeSet(int key) {
	disJointSet *x = (disJointSet*)malloc(sizeof(disJointSet));
	x->rank = 0;
	x->key = key;
	x->p = x;
	return x;
}
void linkSet(disJointSet *x, disJointSet *y) {
	if (x->rank < y->rank) {
		y->p = x;
	}
	else {
		x->p = y;
		if (x->rank == y->rank) {
			y->rank++;
		}
	}
}
disJointSet* findSet(disJointSet* x) {
	if (x != x->p) {
		x->p = findSet(x->p);
	}
	return x->p;
}
void unionSet(disJointSet* x, disJointSet* y) {
	linkSet(findSet(x), findSet(y));
}
void demo() {
	disJointSet* sets[10];
	for (int i = 0; i < 10; i++) {
		sets[i] = makeSet(i);
	}
	for (int i = 0; i < 3; i++) {
		unionSet(sets[i], sets[i + 1]);
	}
	// 0 -> 1 -> 2 -> 3 -> 4
	unionSet(sets[5], sets[7]);
	// 5 -> 7
	unionSet(sets[6], sets[8]);
	unionSet(sets[8], sets[9]);
	// 6 -> 8 -> 9

	for (int i = 0; i < 10; i++) {
		printf("[%d] - r: %d\n", sets[i]->key, sets[i]->rank);
	}

	printf("%d ", findSet(sets[8])->key);
	printf("%d ", findSet(sets[2])->key);
	printf("%d ", findSet(sets[5])->key);
	printf("%d ", findSet(sets[7])->key);
	printf("%d ", findSet(sets[6])->key);

}

int main() {
	demo();
}